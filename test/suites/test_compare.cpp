#include <gtest/gtest.h>
#include "cpp-json-qi/json.h"

using namespace jsonqi;

TEST(JsonNull, CanBecompared) {
  json_value vv1;
  json_value vv2;
  ASSERT_TRUE(vv1.is_null());
  ASSERT_TRUE(vv2.is_null());
  ASSERT_TRUE(vv1 == vv2);
}

TEST(JsonBool, CanBeCompared) {
  json_value vv1 = true;
  json_value vv2 = true;
  ASSERT_TRUE(vv1 == vv2);

  vv2 = false;
  ASSERT_TRUE(vv1 != vv2);
}

TEST(JsonNumber, CanBeCompared) {
  json_value vv1 = 10.0;
  json_value vv2 = 10.0;
  ASSERT_TRUE(vv1 == vv2);

  vv2 = 11.0;
  ASSERT_TRUE(vv1 != vv2);
}

TEST(JsonString, CanBeCompared) {
  json_value vv1 = json_string("123");
  json_value vv2 = json_string("123");
  ASSERT_TRUE(vv1 == vv2);

  vv2 = json_string("456");
  ASSERT_TRUE(vv1 != vv2);
}

TEST(JsonWString, CanBeCompared) {
  wjson_value vv1 = wjson_string(L"123");
  wjson_value vv2 = wjson_string(L"123");
  ASSERT_TRUE(vv1 == vv2);

  vv2 = wjson_string(L"456");
  ASSERT_TRUE(vv1 != vv2);
}

TEST(JsonArray, CanBeCompared) {
  json_array arr1;
  arr1.push_back(json_string("123"));
  arr1.push_back(json_string("456"));

  json_array arr2;
  arr2.push_back(json_string("123"));
  arr2.push_back(json_string("456"));

  ASSERT_TRUE(arr1 == arr2);

  arr2.back() = json_string("789");
  ASSERT_TRUE(arr1 != arr2);
}

TEST(JsonWArray, CanBeCompared) {
  wjson_array arr1;
  arr1.push_back(wjson_string(L"123"));
  arr1.push_back(wjson_string(L"456"));

  wjson_array arr2;
  arr2.push_back(wjson_string(L"123"));
  arr2.push_back(wjson_string(L"456"));

  ASSERT_TRUE(arr1 == arr2);

  arr2.back() = wjson_string(L"789");
  ASSERT_TRUE(arr1 != arr2);
}

TEST(JsonObject, CanBeCompared) {
  json_array arr1;
  arr1.push_back(1.0);
  arr1.push_back(2.0);
  ASSERT_FALSE(arr1.empty());

  json_object obj2;
  obj2["param1"] = false;
  ASSERT_FALSE(obj2.empty());

  json_object obj_a;
  obj_a["var1"] = nullptr;
  obj_a["var2"] = true;
  obj_a["var3"] = json_string("some text");
  obj_a["var4"] = 12.45;
  obj_a["var5"] = arr1;
  obj_a["var6"] = obj2;
  ASSERT_FALSE(obj_a.empty());

  json_object obj_b;
  obj_b["var1"] = nullptr;
  obj_b["var2"] = true;
  obj_b["var3"] = json_string("some text");
  obj_b["var4"] = 12.45;
  obj_b["var5"] = arr1;
  obj_b["var6"] = obj2;
  ASSERT_FALSE(obj_b.empty());

  ASSERT_TRUE(obj_a == obj_b);

  obj_b["var3"] = 98.89;
  ASSERT_TRUE(obj_a != obj_b);
}
