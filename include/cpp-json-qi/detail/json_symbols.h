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

      static constexpr const char quotation_mark() { return '"'; }
      static constexpr const char reverse_solidus() { return '\\'; }
      static constexpr const char solidus() { return '/'; }
      static constexpr const char backspace() { return '\b'; }
      static constexpr const char formfeed() { return '\f'; }
      static constexpr const char newline() { return '\n'; }
      static constexpr const char carriage_return() { return '\r'; }
      static constexpr const char horizontal_tab() { return '\t'; }

      static constexpr const char open_square_bracket() { return '['; }
      static constexpr const char close_square_bracket() { return ']'; }
      static constexpr const char open_curly_bracket() { return '{'; }
      static constexpr const char close_curly_bracket() { return '}'; }
      static constexpr const char comma() { return ','; }
      static constexpr const char zero() { return '0'; }
      static constexpr const char space() { return ' '; }
      static constexpr const char colon() { return ':'; }

      static const char* const tag_quotation_mark_start() { return "\\\""; }
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

      static constexpr const wchar_t quotation_mark() { return L'"'; }
      static constexpr const wchar_t reverse_solidus() { return L'\\'; }
      static constexpr const wchar_t solidus() { return L'/'; }
      static constexpr const wchar_t backspace() { return L'\b'; }
      static constexpr const wchar_t formfeed() { return L'\f'; }
      static constexpr const wchar_t newline() { return L'\n'; }
      static constexpr const wchar_t carriage_return() { return L'\r'; }
      static constexpr const wchar_t horizontal_tab() { return L'\t'; }

      static constexpr const wchar_t open_square_bracket() { return L'['; }
      static constexpr const wchar_t close_square_bracket() { return L']'; }
      static constexpr const wchar_t open_curly_bracket() { return L'{'; }
      static constexpr const wchar_t close_curly_bracket() { return L'}'; }
      static constexpr const wchar_t comma() { return L','; }
      static constexpr const wchar_t zero() { return L'0'; }
      static constexpr const wchar_t space() { return L' '; }
      static constexpr const wchar_t colon() { return L':'; }

      static const wchar_t* const tag_quotation_mark_start() { return L"\\\""; }
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
