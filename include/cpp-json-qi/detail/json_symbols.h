#pragma once

#include <ios>
#include <cctype>
#include <cwctype>

#if defined(_MSC_VER)
#pragma warning( push )
// disable warning from boost headers
#pragma warning( disable:4459 )
#endif

#include <boost/spirit/include/qi_string.hpp>

#if defined(_MSC_VER)
#pragma warning( pop )
#endif


namespace jsonqi {
  namespace detail {

    template <typename CharT>
    struct json_symbols;

    template <>
    struct json_symbols<char>
    {
      typedef boost::spirit::standard::space_type space_type;

      static const char* const tag_null() { return "null"; }
      static const char* const tag_true() { return "true"; }
      static const char* const tag_false() { return "false"; }

      static const char* const tag_pair_separator() { return ": "; }

      static const char quatation_mark = '"';
      static const char reverse_solidus = '\\';
      static const char solidus = '/';
      static const char backspace = '\b';
      static const char formfeed = '\f';
      static const char newline = '\n';
      static const char carriage_return = '\r';
      static const char horizontal_tab = '\t';

      static const char open_square_bracket = '[';
      static const char close_square_bracket = ']';
      static const char open_curly_bracket = '{';
      static const char close_curly_bracket = '}';
      static const char comma = ',';
      static const char zero = '0';
      static const char space = ' ';
      static const char colon = ':';

      static const char* const tag_quatation_mark_start() { return "\\\""; }
      static const char* const tag_reverse_solidus_start() { return "\\\\"; }
      static const char* const tag_solidus_start() { return "\\/"; }
      static const char* const tag_backspace_start() { return "\\b"; }
      static const char* const tag_formfeed_start() { return "\\f"; }
      static const char* const tag_newline_start_start() { return "\\n"; }
      static const char* const tag_carriage_return_start() { return "\\r"; }
      static const char* const tag_horizontal_tab_start() { return "\\t"; }
      static const char* const tag_non_printable_start() { return "\\u"; }

      static bool isprint(char ch)
      {
        return (std::isprint(static_cast<int>(static_cast<unsigned char>(ch))) != 0);
      }
    };

    template <>
    struct json_symbols<wchar_t>
    {
      typedef boost::spirit::standard_wide::space_type space_type;

      static const wchar_t* const tag_null() { return L"null"; }
      static const wchar_t* const tag_true() { return L"true"; }
      static const wchar_t* const tag_false() { return L"false"; }

      static const wchar_t* const tag_pair_separator() { return L" : "; }

      static const wchar_t quatation_mark = L'"';
      static const wchar_t reverse_solidus = L'\\';
      static const wchar_t solidus = L'/';
      static const wchar_t backspace = L'\b';
      static const wchar_t formfeed = L'\f';
      static const wchar_t newline = L'\n';
      static const wchar_t carriage_return = L'\r';
      static const wchar_t horizontal_tab = L'\t';

      static const wchar_t open_square_bracket = L'[';
      static const wchar_t close_square_bracket = L']';
      static const wchar_t open_curly_bracket = L'{';
      static const wchar_t close_curly_bracket = L'}';
      static const wchar_t comma = L',';
      static const wchar_t zero = L'0';
      static const wchar_t space = L' ';
      static const wchar_t colon = L':';

      static const wchar_t* const tag_quatation_mark_start() { return L"\\\""; }
      static const wchar_t* const tag_reverse_solidus_start() { return L"\\\\"; }
      static const wchar_t* const tag_solidus_start() { return L"\\/"; }
      static const wchar_t* const tag_backspace_start() { return L"\\b"; }
      static const wchar_t* const tag_formfeed_start() { return L"\\f"; }
      static const wchar_t* const tag_newline_start_start() { return L"\\n"; }
      static const wchar_t* const tag_carriage_return_start() { return L"\\r"; }
      static const wchar_t* const tag_horizontal_tab_start() { return L"\\t"; }
      static const wchar_t* const tag_non_printable_start() { return L"\\u"; }

      static bool isprint(wchar_t ch)
      {
        return (std::iswprint(static_cast<wint_t>(ch)) != 0);
      }
    };

  } // namespace detail
} // namespace jsonqi
