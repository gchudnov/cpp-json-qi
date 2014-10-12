#include <gtest/gtest.h>
#include "../../include/cpp-json-qi/json.h"

using namespace jsonqi;

TEST(JsonValue, CanBeConvertedToNull) {
  json_value jval = nullptr;
  nullptr_t v1 = to_null(jval);
  ASSERT_TRUE(v1 == nullptr);
}

TEST(JsonValue, CanBeConvertedToBool) {
  json_value jval = true;
  bool v2 = to_bool(jval);
  ASSERT_EQ(true, v2);
}

TEST(JsonValue, CanBeConvertedToDouble) {
  json_value jval = 33.1;
  double v3 = to_number(jval);
  EXPECT_DOUBLE_EQ(33.1, v3);
}

TEST(JsonValue, CanBeConvertedToString) {
  json_value jval = std::string("test");
  std::string v4 = to_string(jval);
  ASSERT_EQ(json_string("test"), v4);
}

TEST(JsonValue, CanBeConvertedToVector) {
  json_array jarr; // std::vector<value_type>
  ASSERT_TRUE(jarr.empty());
  jarr.push_back(true);
  ASSERT_FALSE(jarr.empty());

  json_value jval = jarr;
  json_array v5 = to_array(jval);
  ASSERT_EQ(1, v5.size());
  ASSERT_EQ(true, v5[0]);
}

TEST(JsonValue, CanBeConvertedToMap) {
  json_object jobj; // std::map<string_type, value_type>
  ASSERT_TRUE(jobj.empty());
  jobj["param1"] = false;
  ASSERT_FALSE(jobj.empty());

  json_value jval = jobj;
  json_object v6 = to_object(jval);
  ASSERT_EQ(1, v6.size());
  ASSERT_EQ(false, v6["param1"]);
}
