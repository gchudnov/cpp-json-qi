#include "gtest/gtest.h"
#include "../../include/cpp-json-qi/json.h"

///////////////////////////////////////////////////////////////////////////////
TEST(JsonTest, ConBeConverted)
{
  using namespace jsonqi;

  json_null jnull = nullptr;
  json_bool jbool = true;
  json_number jnum = 33.1;
  json_string jstr = json_string("test");

  json_array jarr;
  ASSERT_TRUE(jarr.empty());
  jarr.push_back(true);
  ASSERT_FALSE(jarr.empty());

  json_object jobj;
  ASSERT_TRUE(jobj.empty());
  jobj["param1"] = false;
  ASSERT_FALSE(jobj.empty());

  // tests
  json_value jval = jnull;
  json_null v1 = to_null(jval);
  ASSERT_TRUE(v1 == nullptr);

  jval = jbool;
  json_bool v2 = to_bool(jval);
  ASSERT_EQ(true, v2);

  jval = jnum;
  json_number v3 = to_number(jval);
  EXPECT_DOUBLE_EQ(33.1, v3);

  jval = jstr;
  json_string v4 = to_string(jval);
  ASSERT_EQ(json_string("test"), v4);

  jval = jarr;
  json_array v5 = to_array(jval);
  ASSERT_EQ(1, v5.size());
  ASSERT_EQ(true, v5[0]);

  jval = jobj;
  json_object v6 = to_object(jval);
  ASSERT_EQ(1, v6.size());
  ASSERT_EQ(false, v6["param1"]);
}
