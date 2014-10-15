#pragma once

#include "json_symbols.h"

#include <string>
#include <ios>
#include <cctype>
#include <cassert>

namespace jsonqi {
  namespace {

    const int formatted_flag_index = std::ios_base::xalloc();
    const int fill_char_index = std::ios_base::xalloc();

    template <typename CharT>
    bool is_formatted(std::basic_ostream<CharT>& os) {
      return (os.iword(formatted_flag_index) != 0);
    }

    template <typename CharT>
    void set_formatted(std::basic_ostream<CharT>& os, bool flag = true) {
      os.iword(formatted_flag_index) = flag;
    }

    template <typename CharT>
    CharT get_fill_char(std::basic_ostream<CharT>& os) {
      return (is_formatted(os) ? static_cast<CharT>(os.iword(fill_char_index)) : detail::json_symbols<CharT>::space());
    }

    template <typename CharT>
    void set_fill_char(std::basic_ostream<CharT>& os, CharT ch) {
      if (detail::json_symbols<CharT>::isprint(ch)) {
        os.iword(fill_char_index) = ch;
        os.fill(ch);
      }
    }

    template <typename CharT>
    void set_fill_char(std::basic_ostream<CharT>& os) {
      CharT ch = get_fill_char(os);
      if (detail::json_symbols<CharT>::isprint(ch)) {
        os.fill(ch);
      }
    }

  } // end of anonymous namespace


  template <typename CharT>
  class indent_formatter {
  public:
    typedef CharT char_type;
    typedef std::basic_ostream<CharT> ostream_type;

  private:
    bool      is_formatted_;
    char_type ch_; // character we use for formatting

  public:
    explicit indent_formatter(bool is_formatted, char_type ch)
      : is_formatted_(is_formatted),
      ch_(ch) {
    }

  private:
    indent_formatter& operator =(const indent_formatter);

  public:
    void set_ostream_info(ostream_type& os) const {
      set_fill_char(os, ch_);
      set_formatted(os, is_formatted_);
    }
  };

  template <typename CharT>
  std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const indent_formatter<CharT>& formatter) {
    formatter.set_ostream_info(os);
    return os;
  }

  // gets a new formatter from the stream
  template <typename CharT>
  indent_formatter<CharT> get_formatter(std::basic_ostream<CharT>& os) {
    return indent_formatter<CharT>(is_formatted(os), get_fill_char(os));
  }


  // FORMAT
  inline indent_formatter<char> format(char ch = detail::json_symbols<char>::space()) {
    return indent_formatter<char>(true, ch);
  }

  inline indent_formatter<wchar_t> wformat(wchar_t ch = detail::json_symbols<wchar_t>::space()) {
    return indent_formatter<wchar_t>(true, ch);
  }

  // DO NOT FORMAT
  inline indent_formatter<char> noformat() {
    return indent_formatter<char>(false, detail::json_symbols<char>::space());
  }

  inline indent_formatter<wchar_t> wnoformat() {
    return indent_formatter<wchar_t>(false, detail::json_symbols<wchar_t>::space());
  }



  namespace detail {

    // put indent in the output stream
    template <typename CharT>
    class indent {
    private:
      typedef std::basic_string<CharT> string_type;
      typedef std::basic_ostringstream<CharT> ostringstream_type;
      typedef std::basic_ostream<CharT> ostream_type;

    private:
      size_t value_;

    public:
      indent(size_t value = 0)
        : value_(value) {
      }

      size_t value() const {
        return value_;
      }
    };

    template <typename CharT>
    std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const indent<CharT>& ind) {
      typedef std::basic_string<CharT> string_type;
      typedef CharT char_type;

      char_type ch = get_fill_char(os);
      assert(ch && "fill character cannot be NULL");
      if (is_formatted(os)) {
        os << std::endl << string_type(ind.value() << 1, ch);
      }
      else {
        os << ch;
      }

      return os;
    }


    // Used to manage ident increment / decrement
    class scope_increment {
    private:
      size_t& value_;

    public:
      explicit scope_increment(size_t& value)
        : value_(++value) {
      }

      ~scope_increment() {
        assert(value_ > 0 && "decrement overflow");
        --value_;
      }

    private:
      scope_increment(const scope_increment& other);
      scope_increment& operator =(const scope_increment& other);
    };


  } // namespace detail

} // namespace jsonqi
