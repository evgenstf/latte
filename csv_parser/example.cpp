// Author: Evgenii Kazakov. Github: @evgenstf
#include "csv_parser.h"
#include <iostream>

using namespace latte;

int main(int arguments_count, char* arguments[]) {
  if (arguments_count < 2) {
    std::clog << "Usage: ./csv_parser [csv_file*]\n";
    return 0;
  }
  for (size_t i = 1; i < arguments_count; ++i) {
    auto file_name = std::string(arguments[i]);
    std::clog << "csv file name: " << file_name << std::endl;
    CsvParser parser(file_name);
    std::clog << "  fields: ";
    for (const auto field : parser.fields()) {
      std::clog << field << ' ';
    }
    std::clog << std::endl;
    for (const auto& item : parser.items()) {
      std::clog << "  ";
      for (const auto& field_and_value : item) {
        std::clog << field_and_value.first << ": " << field_and_value.second << ' ';
      }
      std::clog << std::endl;
    }
    std::clog << std::endl;
  }
  return 0;
}
