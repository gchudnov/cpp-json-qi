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

/////////////////////////////////////////////////////////////////////////////////
//TEST(JsonTest, ReadInput)
//{
//  try
//  {
//    using namespace jsonqi;
//
//    // INPUT
//
//    //std::string input(" \"this is a test string\" ");
//    //std::string input(" 123 ");
//    //std::string input(" true ");
//    //std::string input(" [ 1.98, \"text data\", true ,null ]");
//    std::string input(" { \"key1\" : [ 1.98, \"text data\", true ,null ], \"key2\" : false }");
//
//    std::istringstream iss(input);
//    json_value val;
//    iss >> val;
//    ASSERT_TRUE(!val.is_null());
//
//
//    // OUTPUT
//    std::ostringstream oss;
//    oss << val;
//    std::string result_str = oss.str();
//    ASSERT_FALSE(result_str.empty());
//  }
//  catch (std::exception& ex)
//  {
//    FAIL() << "exception:" << ex.what();
//  }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//TEST(JsonTest, ReadInputWide)
//{
//  try
//  {
//    using namespace jsonqi;
//
//    // INPUT
//    std::wstring input(L" { \"key1\" : [ 1.98, \"text data\", true ,null ], \"key2\" : false }");
//
//    std::wistringstream wiss(input);
//    wjson_value val;
//    wiss >> val;
//    ASSERT_TRUE(!val.is_null());
//
//
//    // OUTPUT
//    std::wostringstream woss;
//    woss << val;
//    std::wstring result_wstr = woss.str();
//    ASSERT_FALSE(result_wstr.empty());
//  }
//  catch (std::exception& ex)
//  {
//    FAIL() << "exception:" << ex.what();
//  }
//}
//
/////////////////////////////////////////////////////////////////////////////////
//TEST(JsonTest, ReadInputSpecial)
//{
//  try
//  {
//    using namespace jsonqi;
//
//    // INPUT
//    std::string input("\"escaped quote\\\"\"");
//    //std::string input("\"plain string\"");
//
//    std::istringstream iss(input);
//    json_value val;
//    iss >> val;
//    ASSERT_TRUE(!val.is_null());
//
//
//    // OUTPUT
//    std::ostringstream oss;
//    oss << val;
//    std::string result_str = oss.str();
//    ASSERT_FALSE(result_str.empty());
//  }
//  catch (std::exception& ex)
//  {
//    FAIL() << "exception:" << ex.what();
//  }
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//TEST(JsonTest, ReadInputWideError)
//{
//  try
//  {
//    using namespace jsonqi;
//
//    // INPUT (with an error -- missing comma)
//    std::wstring input(L" { \"key1\" : [ 1.98, \"text data\", true ,null],  \"key2\"  false }");
//
//    std::wistringstream wiss(input);
//    wjson_value val;
//    wiss >> val;
//
//    FAIL() << "Must throw exception:";
//  }
//  catch (std::exception& /*ex*/)
//  {
//    // ok
//  }
//}
