#include "gtest/gtest.h"
#include "../../include/cpp-json-qi/json.h"

using namespace jsonqi;

TEST(StringValue, CanBeRead) {
  std::string input("\"this is a test string\"");

  std::istringstream iss(input);
  json_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());

  std::ostringstream oss;
  oss << val;
  std::string result_str = oss.str();
  ASSERT_EQ(result_str, input);
}

TEST(NumberValue, CanBeRead) {
  std::string input("123");

  std::istringstream iss(input);
  json_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());

  std::ostringstream oss;
  oss << val;
  std::string result_str = oss.str();
  ASSERT_EQ(result_str, input);
}

TEST(BooleanValue, CanBeRead) {
  std::string input("true");

  std::istringstream iss(input);
  json_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());

  std::ostringstream oss;
  oss << val;
  std::string result_str = oss.str();
  ASSERT_EQ(result_str, input);
}

TEST(ArrayValue, CanBeRead) {
  std::string input("[ 1.98, \"text data\", true ,null ]");

  std::istringstream iss(input);
  json_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());
}

TEST(ObjectValue, CanBeRead) {
  std::string input("{ \"key1\" : [ 1.98, \"text data\", true ,null ], \"key2\" : false }");

  std::istringstream iss(input);
  json_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());
}

TEST(ObjectValue, CanBeReadAsWide) {
  std::wstring input(L"{ \"key1\" : [ 1.98, \"text data\", true ,null ], \"key2\" : false }");

  std::wistringstream iss(input);
  wjson_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());
}

TEST(StringValue, CanBeReadWithEscapedCharacters) {
  std::string input("\"escaped quote\\\"\"");

  std::istringstream iss(input);
  json_value val;
  iss >> val;
  ASSERT_TRUE(!val.is_null());

  std::ostringstream oss;
  oss << val;
  std::string result_str = oss.str();
  ASSERT_EQ(result_str, input);
}


TEST(ReadError, CanBeDetected) {
  try
  {
    // INPUT (with an error -- missing comma)
    std::wstring input(L" { \"key1\" : [ 1.98, \"text data\", true ,null],  \"key2\"  false }");

    std::wistringstream wiss(input);
    wjson_value val;
    wiss >> val;

    FAIL() << "Must throw exception:";
  }
  catch (std::exception& /*ex*/)
  {
    // ok
  }
}
