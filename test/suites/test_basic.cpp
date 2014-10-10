#include "gtest/gtest.h"
#include "../../include/cpp-json-qi/json.h"

///////////////////////////////////////////////////////////////////////////////
TEST(JsonTest, ConBeConstructed)
{
  using namespace jsonqi;

  try
  {
    json_null var1;
    json_bool var2 = true;
    json_number var3 = 12.45;
    json_string var4 = "test string value";
    json_value var5;
    json_pair var6;
    json_array var7;
    json_object var8;

    ASSERT_TRUE(var5.is_null());

    // null
    var5 = var1;
    ASSERT_TRUE(var5.is_null());
    ASSERT_TRUE(is_simple_type(var5));
    ASSERT_FALSE(is_compound_type(var5));
    ASSERT_TRUE(var5.empty());

    // bool
    var5 = var2;
    ASSERT_FALSE(var5.is_null());
    ASSERT_EQ(var2, to_bool(var5));
    ASSERT_TRUE(is_simple_type(var5));
    ASSERT_FALSE(is_compound_type(var5));
    ASSERT_FALSE(var5.empty());

    // clear
    var5.clear();
    ASSERT_TRUE(var5.is_null());
    ASSERT_TRUE(is_simple_type(var5));
    ASSERT_FALSE(is_compound_type(var5));
    ASSERT_TRUE(var5.empty());

    // number
    var5 = var3;
    ASSERT_EQ(var3, to_number(var5));
    ASSERT_TRUE(is_simple_type(var5));
    ASSERT_FALSE(is_compound_type(var5));
    ASSERT_FALSE(var5.empty());

    // string
    var5 = var4;
    ASSERT_EQ(var4, var5.get_value<json_string>());
    ASSERT_EQ(var4, to_string(var5));
    ASSERT_TRUE(is_simple_type(var5));
    ASSERT_FALSE(is_compound_type(var5));
    ASSERT_FALSE(var5.empty());

    // array
    var5 = var7;
    ASSERT_TRUE(to_array(var5).empty());
    ASSERT_FALSE(is_simple_type(var5));
    ASSERT_TRUE(is_compound_type(var5));
    ASSERT_TRUE(var5.empty());

    // object
    var5 = var8;
    ASSERT_TRUE(to_object(var5).empty());
    ASSERT_FALSE(is_simple_type(var5));
    ASSERT_TRUE(is_compound_type(var5));
    ASSERT_TRUE(var5.empty());

    // pair
    std::string sss("test");
    var6 = std::make_pair(sss, var5);
    ASSERT_EQ(sss, var6.first);
    ASSERT_TRUE(to_object(var6.second).empty());

    // invalid cast
    try
    {
      var5 = var4; // assign a string
      json_number num = to_number(var5); // try to get invalud data
      num;

      FAIL() << "Must throw bad_get exception:";
    }
    catch (boost::bad_get& /*ex*/)
    {
      // ok
    }
  }
  catch (std::exception& ex)
  {
    FAIL() << "exception:" << ex.what();
  }
}
