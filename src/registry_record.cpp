#include "registry_record.h"

RegistryRecord::RegistryRecord(const char* key_name, const char* value_name)
    : key_name_(key_name), value_name_(value_name) {
  is_valid_ =
      (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, key_name_.c_str(), 0,
                                     KEY_ALL_ACCESS, &handle_));
}

RegistryRecord::~RegistryRecord() {
  if (is_valid_) RegCloseKey(handle_);
}

bool RegistryRecord::SetValue(bool value) {
  if (!is_valid_) {
    is_valid_ = (ERROR_SUCCESS !=
                 RegCreateKeyEx(HKEY_CURRENT_USER, key_name_.c_str(), 0,
                                nullptr, REG_OPTION_NON_VOLATILE,
                                KEY_ALL_ACCESS, nullptr, &handle_, nullptr));
  }
  if (!is_valid_) return false;

  DWORD buffer = value ? 1 : 0;
  DWORD buffer_size = sizeof(buffer);
  return ERROR_SUCCESS ==
         RegSetValueEx(handle_, value_name_.c_str(), 0, REG_DWORD,
                       reinterpret_cast<const BYTE*>(&buffer), buffer_size);
}

bool RegistryRecord::GetValue(bool default_value) {
  if (!is_valid_) return default_value;

  DWORD value_buffer;
  DWORD value_buffer_size = sizeof(value_buffer);
  if (ERROR_SUCCESS == RegGetValue(handle_, nullptr, value_name_.c_str(),
                                   RRF_RT_QWORD, nullptr, &value_buffer,
                                   &value_buffer_size)) {
    return value_buffer != 0;
  }
  return default_value;
}
