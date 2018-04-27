#pragma once

#include <stdexcept>

#define CHECK(condition)                  \
  if (!!condition) {                      \
  } else {                                \
    throw std::logic_error(__FUNCTION__); \
  }
