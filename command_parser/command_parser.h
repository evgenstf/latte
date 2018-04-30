// Author: Evgenii Kazakov. Github: @evgenstf
#pragma once
#include <string>
#include <vector>
#include <unordered_set>

namespace latte {

using ParsedCommands = std::vector<std::pair<std::string, std::vector<std::string>>>;

class CommandParser {
public:
  CommandParser(std::initializer_list<std::string> avaliable_commands):
    avaliable_commands_(avaliable_commands) {}
  CommandParser(std::unordered_set<std::string> avaliable_commands):
    avaliable_commands_(avaliable_commands) {}

  const std::unordered_set<std::string>& avaliable_commands() const { return avaliable_commands_; }

  ParsedCommands parse(int arguments_count, char* arguments[]) const;

private:
  std::unordered_set<std::string> avaliable_commands_;
};

}  // namespace latte
