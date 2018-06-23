// Author: Evgenii Kazakov. Github: @evgenstf
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace latte {

class CsvParser {
public:
  CsvParser(const std::string& file_name);

  const auto& fields() const { return fields_; }
  const auto& items() const { return items_; }

private:
  std::vector<std::string> fields_;
  std::vector<std::unordered_map<std::string, std::string>> items_;
};

}  // namespace latte
