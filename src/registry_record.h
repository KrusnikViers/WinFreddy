#pragma once

#include <string>

#include "windows.h"

class RegistryRecord {
 public:
  RegistryRecord(std::string key_name);
  ~RegistryRecord();

  // Returns true on success.
  bool SetValue(const std::string& value_name, bool value);
  bool SetValue(const std::string& value_name, const std::string& value);
  bool RemoveValue(const std::string& value_name);

  bool GetBoolValue(const std::string& value_name, bool default_value = true);
  std::string GetStringValue(const std::string& value_name,
                             std::string default_value = std::string());

 private:
  bool is_valid_ = false;
  HKEY handle_;
};  // class RegistryRecord
