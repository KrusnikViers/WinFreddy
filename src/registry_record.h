#pragma once

#include <string>

#include "windows.h"
#include "winreg.h"

class RegistryRecord {
 public:
  RegistryRecord(std::string key_name);
  ~RegistryRecord();

  // Returns true on success.
  bool SetValue(const std::string& value_name, int value);
  bool SetValue(const std::string& value_name, const std::string& value);
  bool RemoveValue(const std::string& value_name);

  int GetIntValue(const std::string& value_name, int default_value = 0);
  std::string GetStringValue(const std::string& value_name,
                             std::string default_value = std::string());

 private:
  bool is_valid_ = false;
  HKEY handle_;
};  // class RegistryRecord
