// Author: Evgenii Kazakov. Github: @evgenstf
#include "file_system_item/file_system_item.h"
#include <iostream>

using namespace latte;

void print_common_information(const FileSystemItem& item) {
  std::cout << "  common properties: \n";
  std::cout << "    path: " << item.path() << '\n';
  std::cout << "    name: " << item.name() << '\n';
  std::cout << "    location: " << item.location() << '\n';
  std::cout << "    exists: " << (item.exists() ? "true" : "false") << '\n';
}

void print_item_information(std::string path) {
  std::cout << "information for item: " << path << '\n';
  FileSystemItem item(std::move(path));
  print_common_information(item);
  std::cout << '\n';
}

int main(int arguments_count, char* arguments[]) {
  if (arguments_count < 2) {
    std::cout << "Usage: ./file_system <file_name1> <file_name2> <file_name3> ...\n";
    return 0;
  }
  for (size_t i = 1; i < arguments_count; ++i) {
    print_item_information(std::string(arguments[i]));
  }
  return 0;
}
