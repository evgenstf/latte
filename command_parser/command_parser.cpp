// Author: Evgenii Kazakov. Github: @evgenstf
#include "command_parser.h"

namespace latte {

ParsedCommands CommandParser::parse(int arguments_count, char* arguments[]) const {
  ParsedCommands result;

  std::string current_command;
  std::vector<std::string> current_parameters;
  for (size_t index = 1; index < arguments_count; ++index) {
    auto argument = std::string(arguments[index]);
    if (avaliable_commands_.find(argument) == avaliable_commands_.end()) {
      current_parameters.push_back(argument);
    } else {
      if (!current_command.empty()) {
        result.emplace_back(std::move(current_command), std::move(current_parameters));
      }
      current_command = argument;
      current_parameters = std::vector<std::string>();
    }
  }
  if (!current_command.empty()) {
    result.emplace_back(std::move(current_command), std::move(current_parameters));
  }

  return result;
}

}  // namespace latte
