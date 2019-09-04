// Author: Evgenii Kazakov. Github: @evgenstf
#pragma once
#include <string>
#include <experimental/filesystem>

namespace latte::filesystem {

class Item {
public:
  Item(std::string path);

  const std::string& path() const { return path_; }
  const std::string& name() const { return name_; }
  const std::string& location() const { return location_; }

  bool exists() const;

private:
  const std::string path_;
  const std::string name_;
  const std::string location_;
};

}  // namespace latte::filesystem
