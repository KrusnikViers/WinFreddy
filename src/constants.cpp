#include "constants.h"

#include "utils.h"

namespace {

std::string GetModuleFilename() {
  char buffer[MAX_PATH + 10];
  CHECK(GetModuleFileName(nullptr, buffer, MAX_PATH + 10));
  return std::string("\"") + std::string(buffer) + std::string("\"");
}

}  // namespace

const std::string kActiveStateTrayIconTip = "Stay awake! (WinFreddy v1.1)";
const std::string kRestStateTrayIconTip = "Computer may sleep. (WinFreddy v1.1)";

const std::string kMenuAutolaunchText = "Launch on system start";
const std::string kMenuRemainActiveText = "Computer will stay awake";
const std::string kMenuAboutText = "Go to the project page";
const std::string kMenuExitText = "Exit";

const std::string kRegistryMainKey = "Software\\KrusnikViers\\WinFreddy";
const std::string kRegistryAutolaunchKey =
    "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const std::string kRegistryDefaultState = "DefaultState";
const std::string kRegistryAppPath = "WinFreddy";

const std::string kModuleFileName = GetModuleFilename();
