#pragma once

#include "json_types.h"
#include "detail/json_format.h"
#include "detail/json_symbols.h"
#include <string>
#include <ostream>
#include <iomanip>
#include <cstdint>
#include <boost/variant.hpp>

namespace jsonqi {

  namespace {

    template <typename CharT>
    struct indent_params
      : public indent_formatter<CharT> {
      typedef CharT char_type;

      size_t    indent;

      explicit indent_params(const indent_formatter& formatter, size_t ind = 0)
        : indent_formatter(formatter),
        indent(ind) {
      }
    };


    template <typename CharT>
    class json_output_visitor
      : public boost::static_visitor<std::basic_string<CharT> > {
    private:
      typedef CharT                           char_type;
      typedef std::basic_ostringstream<CharT> ostringstream_type;
      typedef std::basic_ostream<CharT>       ostream_type;
      typedef indent_params<CharT>            params_type;

      typedef detail::json_symbols<CharT> symbols;
      typedef basic_json_traits<CharT>    json_traits;

      typedef typename json_traits::null_type   null_type;
      typedef typename json_traits::bool_type   bool_type;
      typedef typename json_traits::number_type number_type;
      typedef typename json_traits::string_type string_type;
      typedef typename json_traits::value_type  value_type;
      typedef typename json_traits::array_type  array_type;
      typedef typename json_traits::object_type object_type;
      typedef typename json_traits::pair_type   pair_type;

    private:
      mutable params_type params_;

    public:
      explicit json_output_visitor(const params_type params = params_type())
        : params_(params) {
      }

    private:
      json_output_visitor& operator =(const json_output_visitor&);

    public:
      string_type operator()(const null_type& /*value*/) const {
        return symbols::tag_null();
      }

      string_type operator()(const bool_type& value) const {
        return (value ? symbols::tag_true() : symbols::tag_false());
      }

      string_type operator()(const number_type& value) const {
        ostringstream_type oss;

        oss << value;
        return oss.str();
      }

      string_type operator()(const string_type& str) const {
        ostringstream_type oss;

        oss << symbols::quatation_mark;
        for (string_type::const_iterator it = str.begin(); it != str.end(); ++it) {
          const string_type::value_type& ch = *it;
          switch (ch) {
          case symbols::quatation_mark:
            oss << symbols::tag_quatation_mark_start();
            break;

          case symbols::reverse_solidus:
            oss << symbols::tag_reverse_solidus_start();
            break;

            //case symbols::solidus:
            //    oss << symbols::tag_solidus_start();
            //    break;

          case symbols::backspace:
            oss << symbols::tag_backspace_start();
            break;

          case symbols::formfeed:
            oss << symbols::tag_formfeed_start();
            break;

          case symbols::newline:
            oss << symbols::tag_newline_start_start();
            break;

          case symbols::carriage_return:
            oss << symbols::tag_carriage_return_start();
            break;

          case symbols::horizontal_tab:
            oss << symbols::tag_horizontal_tab_start();
            break;

          default: {
            if (symbols::isprint(ch)) {
              oss << *it;
            }
            else {
              // we have a non-printable character, convert it to 4 hexadecimal digts
              uint16_t uch = static_cast<uint16_t>(static_cast<unsigned char>(ch));
              oss << symbols::tag_non_printable_start() << std::setfill(symbols::zero) << std::setw(4) << std::hex << uch;
            }
          }
            break;
          }
        }
        oss << symbols::quatation_mark;

        return oss.str();
      }

      string_type operator()(const value_type& value) const {
        return boost::apply_visitor(json_output_visitor<CharT>(params_), value.inner());
      }

      string_type operator()(const pair_type& p) const {
        ostringstream_type oss;

        oss << this->operator()(p.first) << symbols::tag_pair_separator() << this->operator()(p.second);

        return oss.str();
      }

      string_type operator()(const array_type& arr) const {
        ostringstream_type oss;
        this->set_stream_params(oss);

        oss << /*detail::indent<char_type>(ind_) <<*/ symbols::open_square_bracket;
        if (!arr.empty()) {
          detail::scope_increment inc(params_.indent);

          array_type::const_iterator it = arr.begin();
          oss << detail::indent<char_type>(params_.indent) << this->operator()(*it);

          ++it;
          while (it != arr.end()) {
            oss << symbols::comma << detail::indent<char_type>(params_.indent) << this->operator()(*it);
            ++it;
          }
        }
        oss << detail::indent<char_type>(params_.indent) << symbols::close_square_bracket;

        return oss.str();
      }

      string_type operator()(const object_type& obj) const {
        ostringstream_type oss;
        this->set_stream_params(oss);

        oss << /*detail::indent<char_type>(ind_) <<*/ symbols::open_curly_bracket;
        if (!obj.empty()) {
          detail::scope_increment inc(params_.indent);

          object_type::const_iterator it = obj.begin();
          oss << detail::indent<char_type>(params_.indent) << this->operator()(*it);

          ++it;
          while (it != obj.end()) {
            oss << symbols::comma << detail::indent<char_type>(params_.indent) << this->operator()(*it);
            ++it;
          }
        }
        oss << detail::indent<char_type>(params_.indent) << symbols::close_curly_bracket;

        return oss.str();
      }

    private:
      void set_stream_params(ostringstream_type& oss) const {
        params_.set_ostream_info(oss);
      }
    };

  } // end of anonymous namespace


  /////////////////////////////////////////////////////////////////////////////////////////
  // Writes JSON data to the ourput stream
  template <typename CharT>
  std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const json_value_impl<CharT>& value) {
    typedef indent_params<CharT> params_type;
    params_type p(get_formatter(os));

    return os << boost::apply_visitor(json_output_visitor<CharT>(p), value.inner()).c_str();
  }

} // namespace jsonqi
