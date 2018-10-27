// Author: Evgenii Kazakov. Github: @evgenstf
#include "csv_parser.h"
#include <fstream>
#include <string>
#include <iostream>


namespace latte {
namespace {

static constexpr char kDelimiter = ',';
static constexpr char kBraceSymbol = '\"';

auto parse_line(const std::string& line) {
  std::vector<std::string> result;
  size_t index = 0;
  bool is_brace_open = false;
  std::string current_item;
  while (index < line.size()) {
    if (index < line.size() && line[index] == kDelimiter) {
      result.emplace_back(std::move(current_item));
      current_item = "";
      ++index;
    }
    while (index < line.size() && (is_brace_open || line[index] != kDelimiter)) {
      if (line[index] == kBraceSymbol) {
        is_brace_open ^= true;
      }
      current_item.push_back(line[index++]);
    }
  }
  if (!current_item.empty() || line.empty()) {
    result.emplace_back(std::move(current_item));
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
