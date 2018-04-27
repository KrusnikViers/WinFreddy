#pragma once

#include <string>

#include "windows.h"

extern const std::string kActiveTip;
extern const std::string kRestTip;

extern const std::string kMenuAutolaunchText;
extern const std::string kMenuAboutText;
extern const std::string kMenuExitText;

extern const std::string kRegistryMainKey;
extern const std::string kRegistryAutolaunchKey;
extern const std::string kRegistryDefaultState;
extern const std::string kRegistryAppPath;

constexpr UINT kAutolaunchItemID = 1u;
constexpr UINT kAboutItemID = kAutolaunchItemID + 1u;
constexpr UINT kExitItemID = kAboutItemID + 1u;
constexpr UINT kIconMessageID = WM_USER + 1u;
