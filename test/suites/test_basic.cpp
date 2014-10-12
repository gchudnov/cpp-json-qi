#include <gtest/gtest.h>
#include "../../include/cpp-json-qi/json.h"

using namespace jsonqi;

TEST(JsonNull, ConBeConstructed) {
  json_null var1;
  ASSERT_TRUE(is_simple_type<char>(var1));
  ASSERT_FALSE(is_compound_type<char>(var1));
}

TEST(JsonBool, ConBeConstructed) {
  json_bool var1 = true;
  json_bool var2 = false;
  ASSERT_TRUE(is_simple_type<char>(var1));
  ASSERT_FALSE(is_compound_type<char>(var1));
  ASSERT_TRUE(is_simple_type<char>(var2));
  ASSERT_FALSE(is_compound_type<char>(var2));
}

TEST(JsonNumber, CanBeConstructed) {
  json_number var1 = 12.45;
  ASSERT_TRUE(is_simple_type<char>(var1));
  ASSERT_FALSE(is_compound_type<char>(var1));
}

TEST(JsonString, CanBeConstructed) {
  json_string var1 = "test string value";
  ASSERT_TRUE(is_simple_type<char>(var1));
  ASSERT_FALSE(is_compound_type<char>(var1));
}

TEST(JsonValue, CanBeConstructed) {
  json_value var1;
  ASSERT_TRUE(var1.is_null());
  ASSERT_TRUE(is_simple_type<char>(var1));
  ASSERT_FALSE(is_compound_type<char>(var1));
}

TEST(JsonValue, CanBeCleared) {
  json_value var1 = true;
  ASSERT_FALSE(var1.is_null());
  var1.clear();
  ASSERT_TRUE(var1.is_null());
  ASSERT_TRUE(is_simple_type(var1));
  ASSERT_FALSE(is_compound_type(var1));
  ASSERT_TRUE(var1.empty());
}

TEST(JsonArray, CanBeConstructed) {
  json_array var1;
  ASSERT_FALSE(is_simple_type<char>(var1));
  ASSERT_TRUE(is_compound_type<char>(var1));
}

TEST(JsonObject, CanBeConstructed) {
  json_object var1;
  ASSERT_FALSE(is_simple_type<char>(var1));
  ASSERT_TRUE(is_compound_type<char>(var1));
}

TEST(JsonNull, CharacteristicsCanBeChecked) {
  json_value var1 = nullptr;
  ASSERT_TRUE(var1.is_null());
  ASSERT_TRUE(is_simple_type(var1));
  ASSERT_FALSE(is_compound_type(var1));
  ASSERT_TRUE(var1.empty());
}

TEST(JsonBool, CharacteristicsCanBeChecked) {
  json_value var1 = true;
  ASSERT_FALSE(var1.is_null());
  ASSERT_EQ(true, to_bool(var1));
  ASSERT_TRUE(is_simple_type(var1));
  ASSERT_FALSE(is_compound_type(var1));
  ASSERT_FALSE(var1.empty());
}

TEST(JsonNumber, CharacteristicsCanBeChecked) {
  json_value var1 = 12.45;
  ASSERT_EQ(12.45, to_number(var1));
  ASSERT_TRUE(is_simple_type(var1));
  ASSERT_FALSE(is_compound_type(var1));
  ASSERT_FALSE(var1.empty());
}

TEST(JsonString, CharacteristicsCanBeChecked) {
  json_value var1 = std::string("test string");
  std::string expected("test string");
  ASSERT_EQ(expected, var1.get_value<json_string>());
  ASSERT_EQ(expected, to_string(var1));
  ASSERT_TRUE(is_simple_type(var1));
  ASSERT_FALSE(is_compound_type(var1));
  ASSERT_FALSE(var1.empty());
}

TEST(JsonArray, CharacteristicsCanBeChecked) {
  json_value var1 = json_array();
  ASSERT_TRUE(to_array(var1).empty());
  ASSERT_FALSE(is_simple_type(var1));
  ASSERT_TRUE(is_compound_type(var1));
  ASSERT_TRUE(var1.empty());
}

TEST(JsonObject, CharacteristicsCanBeChecked) {
  json_value var1 = json_object();
  ASSERT_TRUE(to_object(var1).empty());
  ASSERT_FALSE(is_simple_type(var1));
  ASSERT_TRUE(is_compound_type(var1));
  ASSERT_TRUE(var1.empty());
}

TEST(JsonPair, CharacteristicsCanBeChecked) {
  std::string k("test");
  json_value v = json_object();
  json_pair var1 = std::make_pair(k, v);
  ASSERT_EQ(k, var1.first);
  ASSERT_TRUE(to_object(var1.second).empty());
}

TEST(JsonInvalidCast, CanBeDetected) {
  try
  {
    json_value var1 = std::string("test");
    json_number num = to_number(var1);
    num;

    FAIL() << "Must throw bad_get exception:";
  }
  catch (boost::bad_get& /*ex*/)
  {
    // ok
  }
}
