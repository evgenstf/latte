// Author: Evgenii Kazakov. Github: @evgenstf
#include "file_system_item.h"

namespace latte {

namespace {

int last_slash_index(const std::string& path) {
  int index = path.size() - 1;
  while (index >= 0 && path[index] != '/') {
    --index;
  }
  return index;
}

std::string extract_name(const std::string& path) {
  if (path.empty()) {
    return "";
  }
  size_t name_length = path.size() - last_slash_index(path) - 1;
  return path.substr(path.size() - name_length, name_length);
}

std::string extract_location(const std::string& path) {
  if (path.empty()) {
    return "";
  }
  return path.substr(0, last_slash_index(path) + 1);
}

std::string normalize_path(std::string path) {
  if (path.empty()) {
    return path;
  } else if (path.back() == '/') {
    path.pop_back();
  }
  return path;
}

}  // namespace

FileSystemItem::FileSystemItem(std::string path):
      path_(normalize_path(std::move(path))), name_(extract_name(path_)),
      location_(extract_location(path_)) {}

bool FileSystemItem::exists() const {
  return std::experimental::filesystem::exists(path_);
}


}  // namespace latte
