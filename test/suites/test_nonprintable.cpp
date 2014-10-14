#include <gtest/gtest.h>
#include "../../include/cpp-json-qi/json.h"

#include <iostream>

using namespace jsonqi;

TEST(ASCIICharacters, CanBeWritten) {
  json_array arr;
  arr.push_back(json_string("äöüß")); // UTF-8

  std::ostringstream oss;
  oss << json_value(arr);

  std::string actual = oss.str();
  ASSERT_TRUE(!actual.empty());
  ASSERT_EQ(std::string("[ \"\\u00c3\\u00a4\\u00c3\\u00b6\\u00c3\\u00bc\\u00c3\\u009f\" ]"), actual);
}

TEST(WideCharacters, CanBeWritten) {
  wjson_array arr;
  arr.push_back(wjson_string(L"äöüß")); // UTF-8

  std::wostringstream oss;
  oss << wjson_value(arr);

  std::wstring actual = oss.str();
  ASSERT_TRUE(!actual.empty());
  ASSERT_EQ(std::wstring(L"[ \"\\u00e4\\u00f6\\u00fc\\u00df\" ]"), actual);
}
