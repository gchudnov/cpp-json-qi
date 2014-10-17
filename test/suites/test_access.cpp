#include "gtest/gtest.h"
#include "cpp-json-qi/json.h"

using namespace jsonqi;

TEST(JsonValue, CanBeAccessed) {
  std::string input("{\"menu\": {\n"
    "  \"id\": \"file\",\n"
    "  \"value\": \"File\",\n"
    "  \"popup\": {\n"
    "    \"menuitem\": [\n"
    "      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},\n"
    "      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},\n"
    "      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}\n"
    "    ]\n"
    "  }\n"
    "}}");

  std::istringstream iss(input);
  json_value doc;
  iss >> doc;
  ASSERT_TRUE(!doc.is_null());

  json_object obj = to_object(doc);
  json_object menu = to_object(obj["menu"]);

  json_string menu_id = to_string(menu["id"]); // json_string -- std::string
  ASSERT_EQ("file", menu_id);

  json_string menu_value = to_string(menu["value"]);
  ASSERT_EQ("File", menu_value);

  json_object popup = to_object(menu["popup"]);

  json_array menuitem = to_array(popup["menuitem"]); // json_array -- std::vector<json_value>
  ASSERT_EQ(3, menuitem.size());

  json_object item1 = to_object(menuitem[0]);

  json_string item1_value = to_string(item1["value"]);
  ASSERT_EQ("New", item1_value);

  json_string item1_onclick = to_string(item1["onclick"]);
  ASSERT_EQ("CreateNewDoc()", item1_onclick);
}
