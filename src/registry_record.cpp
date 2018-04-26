#include "registry_record.h"

RegistryRecord::RegistryRecord(std::string key_name) {
  is_valid_ =
      (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, key_name.c_str(), 0,
                                     KEY_ALL_ACCESS, &handle_)) ||
      (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, key_name.c_str(), 0,
                                       nullptr, REG_OPTION_NON_VOLATILE,
                                       KEY_ALL_ACCESS, nullptr, &handle_,
                                       nullptr));
}

RegistryRecord::~RegistryRecord() {
  if (is_valid_)
    RegCloseKey(handle_);
}

bool RegistryRecord::SetValue(const std::string& value_name, int value) {
  return is_valid_ &&
         ERROR_SUCCESS == RegSetValueEx(handle_, value_name.c_str(), 0,
                                        REG_DWORD,
                                        reinterpret_cast<const BYTE*>(&value),
                                        sizeof(value));
}

bool RegistryRecord::SetValue(const std::string& value_name,
                              const std::string& value) {
  return is_valid_ &&
         ERROR_SUCCESS ==
             RegSetValueEx(handle_, value_name.c_str(), 0, REG_SZ,
                           reinterpret_cast<const BYTE*>(value.c_str()),
                           value.size());
}

bool RegistryRecord::RemoveValue(const std::string& value_name) {
  return is_valid_ &&
         ERROR_SUCCESS == RegDeleteValue(handle_, value_name.c_str());
}

int RegistryRecord::GetIntValue(const std::string& value_name,
                                int default_value) {
  DWORD value_buffer = default_value;
  DWORD value_buffer_size = sizeof(value_buffer);
  if (is_valid_ &&
      ERROR_SUCCESS == RegGetValue(handle_, nullptr, value_name.c_str(),
                                   RRF_RT_DWORD, nullptr, &value_buffer,
                                   &value_buffer_size)) {
    return value_buffer;
  }
  return default_value;
}

std::string RegistryRecord::GetStringValue(const std::string& value_name,
                                           std::string default_value) {
  constexpr int string_buffer_size = MAX_PATH + 10;
  char value_buffer[string_buffer_size] = {};
  DWORD value_buffer_size = string_buffer_size;
  if (is_valid_ &&
      ERROR_SUCCESS == RegGetValue(handle_, nullptr, value_name.c_str(),
                                   RRF_RT_REG_SZ, nullptr, &value_buffer,
                                   &value_buffer_size)) {
    return std::string(value_buffer);
  }
  return default_value;
}
