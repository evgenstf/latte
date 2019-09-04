// Author: Evgenii Kazakov. Github: @evgenstf
#pragma once
#include <string>

namespace latte {

class Directory {
public:
  Directory(std::string path): path_(std::move(path)) {}

  const auto& name() const { return name_; }
  const auto& path() const { return path_; }
  const auto& files() const { return files_; }

  bool exists() const { return true; }

private:
  const std::string path_;
  const std::string name_;
  std::vector<File> files_;
};

}  // namespace latte
