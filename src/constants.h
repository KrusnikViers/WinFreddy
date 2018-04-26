#pragma once

#include <string>

#include "windows.h"

extern const std::string kActiveTip;
extern const std::string kRestTip;

extern const std::string kRegistryMainKey;
extern const std::string kRegistryAutolaunchKey;
extern const std::string kRegistryDefaultState;
extern const std::string kRegistryAppPath;

constexpr UINT kIconMessageID = WM_USER + 1;
