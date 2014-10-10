#include "gtest/gtest.h"
#include "../../include/cpp-json-qi/json.h"

///////////////////////////////////////////////////////////////////////////////
TEST(JsonTest, ConBeWritten)
{
  using namespace jsonqi;

  json_object child;
  child["param1"] = 12.0;

  json_array arr;
  arr.push_back(1.0);
  arr.push_back(2.0);
  arr.push_back(3.0);
  arr.push_back(child);


  json_object root;
  root["my_var0"] = json_null();
  root["my_var1"] = true;
  root["my_var2"] = false;
  root["my_var3"] = json_string("text value");
  root["my_var4"] = 8.0;
  root["my_var5"] = arr;

  // without indent
  std::ostringstream oss;
  oss << json_value(root);

  std::string data = oss.str();
  ASSERT_TRUE(!data.empty());
  ASSERT_EQ(142, data.size());


  // with indent
  std::ostringstream oss2;
  oss2 << format() << json_value(root);

  std::string data2 = oss2.str();
  ASSERT_TRUE(!data2.empty());
  ASSERT_EQ(182, data2.size());
}

///////////////////////////////////////////////////////////////////////////////
TEST(JsonTest, WideCharacters)
{
  using namespace jsonqi;

  wjson_array warr;
  json_array  arr;
  warr.push_back(wjson_string(L"Test String"));

  std::wostringstream oss;
  oss << wjson_value(warr);

  std::wstring data = oss.str();
  ASSERT_TRUE(!data.empty());
  ASSERT_EQ(std::wstring(L"[ \"Test String\" ]"), data);
}
