#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cpp-json-qi/json.h>

/**
* Formatting JSON data to read and debug it.
*/
int main(int argc, char* argv[]) {

  std::string input("{\"menu\": { \"id\": \"file\", \"value\": \"File\", \"popup\": { \"menuitem\": [ {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"}, {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"}, {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"} ] } }}");

  std::istringstream iss(input);
  jsonqi::json_value val;
  iss >> val;

  std::ostringstream oss;
  oss << jsonqi::format() << jsonqi::json_value(val);

  std::cout << "unformatted:" << std::endl << input << std::endl << std::endl;
  std::cout << "formatted:" << std::endl << oss.str() << std::endl;

  return EXIT_SUCCESS;
}
