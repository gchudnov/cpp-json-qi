#include "gtest/gtest.h"
#include "../../include/cpp-json-qi/json.h"


TEST(JsonTest, NonPrintableNarrowCanBeWritten)
{
  using namespace jsonqi;

  json_array arr;
  arr.push_back(json_string("äöüß"));
  //arr.push_back(json_string("\a"));

  std::ostringstream oss;
  oss << json_value(arr);

  std::string data = oss.str();
  ASSERT_TRUE(!data.empty());
  ASSERT_EQ(std::string("[ \"\\u00e4\\u00f6\\u00fc\\u00df\" ]"), data);
}


TEST(JsonTest, NonPrintableWideCanBeWritten)
{
  using namespace jsonqi;

  wjson_array warr;
  warr.push_back(wjson_string(L"äöüß"));

  //wjson_string ws(L"δοκιμή");

  std::wostringstream oss;
  oss << wjson_value(warr);

  std::wstring data = oss.str();
  ASSERT_TRUE(!data.empty());
  ASSERT_EQ(std::wstring(L"[ \"äöüß\" ]"), data);
}
