#pragma once

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <boost/variant.hpp>

namespace jsonqi {

  template <typename CharT>
  class json_value_impl;


  // JSON Traits
  template <typename CharT>
  struct basic_json_traits {
    typedef basic_json_traits<CharT> self_type;
    typedef self_type                this_type;

    typedef std::nullptr_t                     null_type;
    typedef bool                               bool_type;
    typedef double                             number_type;
    typedef std::basic_string<CharT>           string_type;
    typedef json_value_impl<CharT>             value_type;
    typedef std::vector<value_type>            array_type;
    typedef std::map<string_type, value_type>  object_type;
    typedef std::pair<string_type, value_type> pair_type;
  };

  namespace {

    // Compare
    template <typename CharT>
    class are_strict_equals
      : public boost::static_visitor<bool> {
    private:
      typedef typename basic_json_traits<CharT> json_traits;

      typedef typename json_traits::null_type   null_type;
      typedef typename json_traits::bool_type   bool_type;
      typedef typename json_traits::number_type number_type;
      typedef typename json_traits::string_type string_type;
      typedef typename json_traits::value_type  value_type;
      typedef typename json_traits::array_type  array_type;
      typedef typename json_traits::object_type object_type;
      typedef typename json_traits::pair_type   pair_type;

    private:
      are_strict_equals& operator =(const are_strict_equals&);

    public:
      template <typename T, typename U>
      bool operator()(const T&, const U&) const {
        return false; // cannot compare different types
      }

      template <typename T>
      bool operator()(const T& lhs, const T& rhs) const {
        return this->is_equal(lhs, rhs);
      }

    private:
      bool is_equal(const null_type& lhs, const null_type& rhs) const {
        return lhs == rhs;
      }

      bool is_equal(const bool_type& lhs, const bool_type& rhs) const {
        return lhs == rhs;
      }

      bool is_equal(const number_type& lhs, const number_type& rhs) const {
        static const double epsilon = 1.0e-08;
        return std::fabs(lhs - rhs) < epsilon;
      }

      bool is_equal(const string_type& lhs, const string_type& rhs) const {
        return lhs == rhs;
      }

      bool is_equal(const array_type& lhs, const array_type& rhs) const {
        if (lhs.size() != rhs.size())
          return false;

        if (lhs.empty())
          return true; // empty ranges are equal

        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
      }

      bool is_equal(const object_type& lhs, const object_type& rhs) const {
        if (lhs.size() != rhs.size())
          return false;

        if (lhs.empty())
          return true; // empty ranges are equal

        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
      }
    };


    // Test if the value is empty
    template <typename CharT>
    class is_empty
      : public boost::static_visitor<bool> {
    private:
      typedef typename basic_json_traits<CharT> json_traits;

      typedef typename json_traits::null_type   null_type;
      typedef typename json_traits::bool_type   bool_type;
      typedef typename json_traits::number_type number_type;
      typedef typename json_traits::string_type string_type;
      typedef typename json_traits::value_type  value_type;
      typedef typename json_traits::array_type  array_type;
      typedef typename json_traits::object_type object_type;
      typedef typename json_traits::pair_type   pair_type;

    public:
      bool operator ()(const null_type& /*value*/) const {
        return true;
      }

      bool operator ()(const bool_type& value) const {
        return (value == false);
      }

      bool operator ()(const number_type& value) const {
        static const double epsilon = 1.0e-08;
        return std::fabs(value - 0.0) < epsilon;
      }

      bool operator ()(const string_type& value) const {
        return (value.empty());
      }

      bool operator ()(const array_type& value) const {
        return (value.empty());
      }

      bool operator ()(const object_type& value) const {
        return (value.empty());
      }
    };


    // Test if the value is a compound type
    template <typename CharT>
    class is_compound
      : public boost::static_visitor<bool> {
    private:
      typedef typename basic_json_traits<CharT> json_traits;
      typedef typename json_traits::array_type  array_type;
      typedef typename json_traits::object_type object_type;

    public:
      template <typename V>
      bool operator ()(const V&) const {
        return false;
      }

      bool operator ()(const array_type& /*value*/) const {
        return true;
      }

      bool operator ()(const object_type& /*value*/) const {
        return true;
      }
    };


  } // end of anonymous namespace


  // Represents a variant value
  template <typename CharT>
  class json_value_impl {
  private:
    typedef json_value_impl<CharT> self_type;
    typedef self_type              this_type;

    typedef typename basic_json_traits<CharT> json_traits;

    typedef typename json_traits::null_type   null_type;
    typedef typename json_traits::bool_type   bool_type;
    typedef typename json_traits::number_type number_type;
    typedef typename json_traits::string_type string_type;
    typedef typename json_traits::value_type  value_type;
    typedef typename json_traits::array_type  array_type;
    typedef typename json_traits::object_type object_type;
    typedef typename json_traits::pair_type   pair_type;

    typedef boost::variant<null_type,
      bool_type,
      number_type,
      string_type,
      boost::recursive_wrapper<array_type>,
      boost::recursive_wrapper<object_type> > variant_type;

  private:
    variant_type v_;    // value

  public:
    json_value_impl()
      : v_(json_null()) {
    }

    json_value_impl(const null_type& value)
      : v_(value) {
    }

    json_value_impl(const bool_type& value)
      : v_(value) {
    }

    json_value_impl(const number_type& value)
      : v_(value) {
    }

    json_value_impl(const string_type& value)
      : v_(value) {
    }

    json_value_impl(const array_type& value)
      : v_(value) {
    }

    json_value_impl(const object_type& value)
      : v_(value) {
    }

  public:
    const std::type_info& type() const {
      return v_.type();
    }

    bool empty() const {
      return (boost::apply_visitor(is_empty<CharT>(), this->v_));
    }

    void clear() {
      v_ = json_null();
    }

    bool is_null() const {
      return (v_.type() == typeid(std::nullptr_t));
    }

    template <typename T>
    const T& get_value() const {
      return boost::get<T>(v_);
    }

    // inner representation
    const variant_type& inner() const {
      return v_;
    }

    // mutable inner representation
    variant_type& inner() {
      return v_;
    }

    void swap(self_type& other) {
      this->v_.swap(other.v_);
    }

  public:
    bool equal_to(const self_type& other) const {
      return (boost::apply_visitor(are_strict_equals<CharT>(), this->v_, other.v_));
    }

    // check for equality
    friend bool operator ==(const self_type& lhs, const self_type& rhs) {
      return lhs.equal_to(rhs);
    }

    friend bool operator !=(const self_type& lhs, const self_type& rhs) {
      return !(lhs == rhs);
    }
  };


  typedef basic_json_traits<char>::null_type   json_null;
  typedef basic_json_traits<char>::bool_type   json_bool;
  typedef basic_json_traits<char>::number_type json_number;
  typedef basic_json_traits<char>::string_type json_string;
  typedef basic_json_traits<char>::value_type  json_value;
  typedef basic_json_traits<char>::array_type  json_array;
  typedef basic_json_traits<char>::object_type json_object;
  typedef basic_json_traits<char>::pair_type   json_pair;

  typedef basic_json_traits<wchar_t>::null_type   wjson_null;
  typedef basic_json_traits<wchar_t>::bool_type   wjson_bool;
  typedef basic_json_traits<wchar_t>::number_type wjson_number;
  typedef basic_json_traits<wchar_t>::string_type wjson_string;
  typedef basic_json_traits<wchar_t>::value_type  wjson_value;
  typedef basic_json_traits<wchar_t>::array_type  wjson_array;
  typedef basic_json_traits<wchar_t>::object_type wjson_object;
  typedef basic_json_traits<wchar_t>::pair_type   wjson_pair;



  // Convinience routines
  template <typename CharT>
  const typename basic_json_traits<CharT>::null_type& to_null(const json_value_impl<CharT>& value) {
    // boost/utility/addressof.hpp(59): error C2666: 'boost::detail::addressof_impl<T>::f' : 2 overloads have similar conversions
    //return value.get_value<std::nullptr_t>();

    typedef typename basic_json_traits<CharT>::null_type null_type;
    if (!value.is_null())
      throw boost::bad_get();

    static const null_type result;
    return result;
  }

  template <typename CharT>
  const typename basic_json_traits<CharT>::bool_type& to_bool(const json_value_impl<CharT>& value) {
    typedef typename basic_json_traits<CharT>::bool_type bool_type;
    return value.get_value<bool_type>();
  }

  template <typename CharT>
  const typename basic_json_traits<CharT>::number_type& to_number(const json_value_impl<CharT>& value) {
    typedef typename basic_json_traits<CharT>::number_type number_type;
    return value.get_value<number_type>();
  }

  template <typename CharT>
  const typename basic_json_traits<CharT>::string_type& to_string(const json_value_impl<CharT>& value) {
    typedef typename basic_json_traits<CharT>::string_type string_type;
    return value.get_value<string_type>();
  }

  template <typename CharT>
  const typename basic_json_traits<CharT>::array_type& to_array(const json_value_impl<CharT>& value) {
    typedef typename basic_json_traits<CharT>::array_type array_type;
    return value.get_value<array_type>();
  }

  template <typename CharT>
  const typename basic_json_traits<CharT>::object_type& to_object(const json_value_impl<CharT>& value) {
    typedef typename basic_json_traits<CharT>::object_type object_type;
    return value.get_value<object_type>();
  }


  // Test if the value is ARRAY or OBJECT
  template <typename CharT>
  bool is_compound_type(const json_value_impl<CharT>& value) {
    return (boost::apply_visitor(is_compound<CharT>(), value.inner()));
  }

  template <typename CharT>
  bool is_simple_type(const json_value_impl<CharT>& value) {
    return !is_compound_type(value);
  }


} // namespace jsonqi
