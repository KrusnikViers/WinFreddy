#pragma once

#include <stdexcept>
#include <string>

#include "windows.h"

#define CHECK(condition)                  \
  if (!!condition) {                      \
  } else {                                \
    throw std::logic_error(__FUNCTION__); \
  }

inline std::string GetModuleFilename() {
  char buffer[MAX_PATH + 10];
  CHECK(GetModuleFileName(nullptr, buffer, MAX_PATH + 10));
  return std::string(buffer);
}
