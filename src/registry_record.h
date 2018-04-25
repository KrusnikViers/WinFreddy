#pragma once

#include <string>
#include "windows.h"
#include "winreg.h"

class RegistryRecord {
public:
    RegistryRecord(const char* key_name, const char* value_name);
    ~RegistryRecord();

    // Returns true on success.
    bool SetValue(bool value);
    bool GetValue(bool default_value = false);

private:
    std::string key_name_;
    std::string value_name_;
    bool is_valid_ = false;
    HKEY handle_;
};  // class RegistryRecord
