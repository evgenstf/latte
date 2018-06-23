// Author: Evgenii Kazakov. Github: @evgenstf
#include "csv_parser.h"
#include <fstream>
#include <string>
#include <iostream>


namespace latte {
namespace {

static constexpr char kDelimiter = ',';

auto parse_line(const std::string& line) {
  std::vector<std::string> result;
  size_t index = 0;
  while (index < line.size()) {
    while (index < line.size() && line[index] == kDelimiter) {
      ++index;
    }
    if (index < line.size()) {
      result.emplace_back();
    }
    while (index < line.size() && line[index] != kDelimiter) {
      result.back().push_back(line[index++]);
    }
  }
  return result;
}

auto remove_carriage_return(std::string line) {
  if (!line.empty() && line.back() == '\r') {
    line.pop_back();
  }
  return line;
}

}  // namespace

CsvParser::CsvParser(const std::string& file_name) {
  std::ifstream file(file_name);
  if (file.fail()) {
    return;
  }
  std::string line;
  getline(file, line);
  line = remove_carriage_return(std::move(line));
  fields_ = parse_line(line);
  while (getline(file, line)) {
    line = remove_carriage_return(std::move(line));
    auto values = parse_line(line);
    std::unordered_map<std::string, std::string> item;
    for (size_t i = 0; i < values.size(); ++i) {
      item[fields_[i]] = values[i];
    }
    items_.emplace_back(std::move(item));
  }
}

}  // namespace latte
