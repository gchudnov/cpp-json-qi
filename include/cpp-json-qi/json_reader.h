#pragma once

#include "json_types.h"
#include "json_error.h"
#include "detail/json_symbols.h"
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <cassert>
#include <boost/spirit/version.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_confix.hpp>

// for error handling
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/at_c.hpp>


namespace jsonqi {

  namespace {

    // Used to insert a new value
    template <typename CharT>
    class value_inserter
      : public boost::static_visitor<void> {
    private:
      typedef CharT char_type;

      typedef basic_json_traits<CharT>    json_traits;

      typedef typename json_traits::null_type   null_type;
      typedef typename json_traits::bool_type   bool_type;
      typedef typename json_traits::number_type number_type;
      typedef typename json_traits::string_type string_type;
      typedef typename json_traits::value_type  value_type;
      typedef typename json_traits::array_type  array_type;
      typedef typename json_traits::object_type object_type;
      typedef typename json_traits::pair_type   pair_type;

      typedef std::stack<value_type*> stack_type;


    private:
      const value_type&   v_;     // a value to insert
      const string_type&  key_;   // key of the key-value pair (used to insert members into the object)
      stack_type&         col_;   // nested values

    public:
      value_inserter(stack_type& col, const string_type& str, const value_type& v)
        : col_(col),
        key_(str),
        v_(v) {
      }

    private:
      value_inserter& operator =(const value_inserter&);

    public:
      template <typename V>
      void operator ()(V& /*value*/) {
        assert(false && "cannot add the element to a simple entry.");
      }

      void operator ()(array_type& arr) {
        arr.push_back(v_);

        if (is_compound_type(v_))
          col_.push(&arr.back());
      }

      void operator ()(object_type& obj) {
        obj[key_] = v_;

        if (is_compound_type(v_))
          col_.push(&obj[key_]);
      }
    };


  }


  // Semantic Actions
  template <typename Iterator, typename CharT>
  class json_semantic_actions {
  private:
    typedef CharT                        char_type;
    typedef std::vector<CharT>           char_vector_type;

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

    typedef std::stack<value_type*> stack_type;


  private:
    value_type&  value_;
    stack_type   col_;      // nested values
    string_type  key_; // key of the key-value pair (used to insert members into the object)

  public:
    json_semantic_actions(value_type& v)
      : value_(v) {
    }

  private:
    json_semantic_actions& operator =(const json_semantic_actions&);

  public:
    void on_object_begin(char_type ch, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      assert(ch == symbols::open_curly_bracket); ch;
      this->add_begin(object_type());
    }

    void on_object_end(char_type ch, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      assert(ch == symbols::close_curly_bracket); ch;
      this->add_end();
    }

    void on_array_begin(char_type ch, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      assert(ch == symbols::open_square_bracket); ch;
      this->add_begin(array_type());
    }

    void on_array_end(char_type ch, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      assert(ch == symbols::close_square_bracket); ch;
      this->add_end();
    }

    void on_pair_key(const char_vector_type& value, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      key_.assign(value.begin(), value.end());
    }

    void on_chars_value(const char_vector_type& value, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      this->add_begin(value_type(string_type(value.begin(), value.end())));
    }

    void on_number_value(double value, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      this->add_begin(value_type(value));
    }

    void on_bool_value(bool value, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      this->add_begin(value_type(value));
    }

    void on_null_value(const string_type& /*value*/, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
      this->add_begin(value_type(nullptr));
    }

    void on_error(const string_type& params, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) {
    }


  private:
    void add_begin(const value_type& v) {
      if (col_.empty()) {
        this->insert_new_root(v);
      }
      else {
        // add new element to the container
        value_type* ptop = col_.top();
        value_inserter<CharT> ins(col_, key_, v);
        boost::apply_visitor(ins, ptop->inner());
      }
    }

    // Finish adding value to the tree
    void add_end() {
      assert(!col_.empty() && is_compound_type(*col_.top()) && "Tree element must be an object or array.");
      if (!col_.empty())
        col_.pop();
    }

    // Insert a new root
    void insert_new_root(const value_type& v) {
      value_ = v;
      if (is_compound_type(value_)) {
        col_.push(&value_);
      }
    }
  };


  // Grammar
  template <typename Iterator, typename CharT>
  struct basic_json_grammar
    : public boost::spirit::qi::grammar<Iterator, typename detail::json_symbols<CharT>::space_type> {
    typedef CharT                       char_type;
    typedef std::basic_string<CharT>    string_type;
    typedef std::vector<CharT>          char_vector_type;

    typedef detail::json_symbols<CharT>  symbols;
    typedef typename symbols::space_type qi_space_type;

    typedef json_semantic_actions<Iterator, CharT> actions_type;

    typedef boost::spirit::qi::rule<Iterator, qi_space_type>                     rule_type;
    typedef boost::spirit::qi::rule<Iterator, char_vector_type(), qi_space_type> chars_rule_type;
    typedef boost::spirit::qi::symbols<char_type, char_type>                     esc_char_type;

    typedef std::function<void(double, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type)> action_number_callback;
    typedef std::function<void(char_type, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type)> action_char_callback;
    typedef std::function<void(bool, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type)> action_bool_callback;
    typedef std::function<void(const char_vector_type&, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type)> action_chars_callback;
    typedef std::function<void(const string_type&, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type)> action_string_callback;

    actions_type& ractions;

    rule_type     rjson;
    rule_type     robject;
    rule_type     rmembers;
    rule_type     rpair;
    rule_type     rarray;
    rule_type     relements;
    rule_type     rvalue;
    chars_rule_type rstring;
    rule_type     rnumber;
    esc_char_type resc_char;

    // callbacks
    action_string_callback  on_null;
    action_bool_callback    on_bool;
    action_number_callback  on_number;
    action_chars_callback   on_chars;
    action_chars_callback   on_pair_key;
    action_char_callback    on_array_begin;
    action_char_callback    on_array_end;
    action_char_callback    on_object_begin;
    action_char_callback    on_object_end;

  public:
    basic_json_grammar(actions_type& a)
      : basic_json_grammar::base_type(rjson, "json_grammar"),
      ractions(a) {
      namespace qi = boost::spirit::qi;
      namespace repo = boost::spirit::repository;

      resc_char.add(symbols::tag_quatation_mark_start(), symbols::quatation_mark)
        (symbols::tag_reverse_solidus_start(), symbols::reverse_solidus)
        (symbols::tag_solidus_start(), symbols::solidus)
        (symbols::tag_backspace_start(), symbols::backspace)
        (symbols::tag_formfeed_start(), symbols::formfeed)
        (symbols::tag_newline_start_start(), symbols::newline)
        (symbols::tag_carriage_return_start(), symbols::carriage_return)
        (symbols::tag_horizontal_tab_start(), symbols::horizontal_tab)
        //(symbols::tag_non_printable_start(), symbols::)
        ;

      on_null = (std::bind(&actions_type::on_null_value, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_bool = (std::bind(&actions_type::on_bool_value, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_number = (std::bind(&actions_type::on_number_value, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_chars = (std::bind(&actions_type::on_chars_value, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_pair_key = (std::bind(&actions_type::on_pair_key, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_array_begin = (std::bind(&actions_type::on_array_begin, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_array_end = (std::bind(&actions_type::on_array_end, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_object_begin = (std::bind(&actions_type::on_object_begin, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
      on_object_end = (std::bind(&actions_type::on_object_end, std::ref(ractions), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


      rstring
        = qi::lexeme
        [
          repo::confix(symbols::quatation_mark, symbols::quatation_mark)[*(resc_char | (qi::char_ - symbols::quatation_mark))]
          //qi::omit[symbols::quatation_mark] >> *(resc_char | (qi::char_ - symbols::quatation_mark)) >> qi::omit[symbols::quatation_mark]
          //repo::confix(symbols::quatation_mark, symbols::quatation_mark)[*(qi::char_ - symbols::quatation_mark)]
        ]
      ;

      rnumber
        = qi::double_[on_number]
        ;

      relements
        = rvalue > *(symbols::comma > rvalue)
        ;

      rarray
        = qi::char_(symbols::open_square_bracket)[on_array_begin]
            > *relements
            > qi::char_(symbols::close_square_bracket)[on_array_end]
            ;

      rpair
        = rstring[on_pair_key]
            > qi::char_(symbols::colon)
            > rvalue
            ;

      rmembers
        = rpair > *(symbols::comma > rpair)
        ;

      robject
        = qi::char_(symbols::open_curly_bracket)[on_object_begin]
            > *rmembers
            > qi::char_(symbols::close_curly_bracket)[on_object_end]
            ;

      rvalue
        = rstring[on_chars]
        | rnumber
        | robject
        | rarray
        | qi::bool_[on_bool]
        | qi::string(symbols::tag_null())[on_null]
        ;

      rjson
        = rvalue.alias()
        ;


      // error detection & handling
      typedef
        boost::fusion::vector<
        const Iterator&     // first - The position of the iterator when the rule with the handler was entered. 
        , const Iterator&     // last  - The end of input.
        , const Iterator&     // error_pos - The actual position of the iterator where the error occurred. 
        , const qi::info&>    // what - What failed: a string decribing the failure. 
        params;

      qi::on_error<qi::fail>
        (
        rjson,
        [](const params& p, boost::spirit::qi::unused_type, boost::spirit::qi::unused_type) -> void {
        namespace fusion = boost::fusion;

        std::ostringstream oss;
        oss << "Parsing failed. Expected: "
          << fusion::at_c<3>(p)
          << " at ("
          << std::distance(fusion::at_c<0>(p), fusion::at_c<2>(p))
          << "): \""
          << std::string(fusion::at_c<2>(p), fusion::at_c<1>(p))
          << "\"";

        throw json_error(oss.str());
      }
      );

      robject.name("object");
      rmembers.name("members");
      rpair.name("pair");
      rarray.name("array");
      relements.name("elements");
      rvalue.name("value");
      rstring.name("string");
      rnumber.name("number");
    }

  private:
    basic_json_grammar& operator =(const basic_json_grammar&);
  };


  // Parse the input and fill the value
  template <typename Iterator, typename CharT>
  bool parse_value(Iterator first, Iterator last, json_value_impl<CharT>& value) {
    typedef json_value_impl<CharT>                 value_type;
    typedef basic_json_grammar<Iterator, CharT>    json_grammar_type;
    typedef json_semantic_actions<Iterator, CharT> actions_type;

    typedef detail::json_symbols<CharT>  symbols;
    typedef typename symbols::space_type qi_space_type;

    value_type temp;
    actions_type act(temp);
    json_grammar_type gr(act);

    bool r = boost::spirit::qi::phrase_parse(first, last, gr, qi_space_type());

    if (!r || first != last) // fail if we did not get a full match
      return false;

    value.swap(temp);

    return true;
  }



  // Reads JSON data
  template <typename CharT>
  std::basic_istream<CharT>& operator >>(std::basic_istream<CharT>& is, json_value_impl<CharT>& value) {
    typedef std::basic_string<CharT>        string_type;
    typedef std::basic_istream<CharT>       istream_type;
    typedef std::istreambuf_iterator<CharT> iterator_type;
    typedef json_value_impl<CharT>          json_valye_type;

    // We need a ForwardIterator, so we copy stream to a string
    string_type storage;
    is.unsetf(std::ios::skipws);
    std::copy(iterator_type(is), iterator_type(), std::back_inserter(storage));
    typename string_type::const_iterator first = storage.begin();
    typename string_type::const_iterator last = storage.end();

    //boost::spirit::multi_pass<base_iterator_type> first = boost::spirit::make_default_multi_pass(base_iterator_type(is));
    //boost::spirit::multi_pass<base_iterator_type> last = boost::spirit::make_default_multi_pass(base_iterator_type());

    // Parse the input
    parse_value(first, last, value);

    return is;
  }

} // namespace jsonqi
