#include "gtest/gtest.h"
#include "../../include/cpp-json-qi/json.h"

using namespace jsonqi;

TEST(JsonValue, CanBeWrittenToStringWithoutIndent) {
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

  std::ostringstream oss;
  oss << json_value(root);

  std::string actual = oss.str();
  ASSERT_TRUE(!actual.empty());

  std::string expected("{ \"my_var0\": null, \"my_var1\": true, \"my_var2\": false, \"my_var3\": \"text value\", \"my_var4\": 8, \"my_var5\": [ 1, 2, 3, { \"param1\": 12 } ] }");
  ASSERT_EQ(expected, actual);
}

TEST(JsonValue, CanBeWrittenToStringWithIndent) {
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

  std::ostringstream oss;
  oss << format() << json_value(root);

  std::string actual = oss.str();
  ASSERT_TRUE(!actual.empty());

  std::string expected("{\n"
    "  \"my_var0\": null,\n"
    "  \"my_var1\": true,\n"
    "  \"my_var2\": false,\n"
    "  \"my_var3\": \"text value\",\n"
    "  \"my_var4\": 8,\n"
    "  \"my_var5\": [\n"
    "    1,\n"
    "    2,\n"
    "    3,\n"
    "    {\n"
    "      \"param1\": 12\n"
    "    }\n"
    "  ]\n"
    "}");
  ASSERT_EQ(expected, actual);
}

TEST(JsonValue, CanBeWrittenToWString) {
  wjson_array warr;
  json_array  arr;
  warr.push_back(wjson_string(L"Test String"));

  std::wostringstream oss;
  oss << wjson_value(warr);

  std::wstring data = oss.str();
  ASSERT_TRUE(!data.empty());
  ASSERT_EQ(std::wstring(L"[ \"Test String\" ]"), data);
}
