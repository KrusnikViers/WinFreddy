#pragma once

#include <string>

#include "windows.h"

extern const std::string kActiveStateTrayIconTip;
extern const std::string kRestStateTrayIconTip;

extern const std::string kMenuAutolaunchText;
extern const std::string kMenuRemainActiveText;
extern const std::string kMenuAboutText;
extern const std::string kMenuExitText;

extern const std::string kRegistryMainKey;
extern const std::string kRegistryAutolaunchKey;
extern const std::string kRegistryDefaultState;
extern const std::string kRegistryAppPath;

extern const std::string kModuleFileName;

enum class MenuID : UINT {
  Autolaunch = 1u,
  RemainActive,
  About,
  Exit,
};

constexpr UINT kIconMessageID = WM_USER + 1u;
