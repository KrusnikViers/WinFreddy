#include "tray_menu.h"

#include "constants.h"
#include "registry_record.h"
#include "utils.h"

namespace {

const std::string kModuleFileName = GetModuleFilename();

}  // namespace

TrayMenu::TrayMenu(HWND window_handle) : window_handle_(window_handle) {
  handle_ = CreatePopupMenu();
  CHECK(handle_);

  AppendMenu(handle_, 0, (UINT_PTR)kAutolaunchItemID,
             kMenuAutolaunchText.c_str());
  AppendMenu(handle_, MF_SEPARATOR, (UINT_PTR)0, nullptr);
  AppendMenu(handle_, 0u, (UINT_PTR)kAboutItemID, kMenuAboutText.c_str());
  AppendMenu(handle_, MF_SEPARATOR, (UINT_PTR)0, nullptr);
  AppendMenu(handle_, 0u, (UINT_PTR)kExitItemID, kMenuExitText.c_str());
}

TrayMenu::~TrayMenu() {
  if (handle_)
    DestroyMenu(handle_);
}

void TrayMenu::ShowMenu(int x, int y) {
  const bool is_autolaunch_set =
      RegistryRecord(kRegistryAutolaunchKey).GetStringValue(kRegistryAppPath) ==
      kModuleFileName;
  ModifyMenu(handle_, kAutolaunchItemID, is_autolaunch_set ? MF_CHECKED : 0u,
             (UINT_PTR)kAutolaunchItemID, kMenuAutolaunchText.c_str());
  TrackPopupMenu(handle_, 0u, x, y, 0, window_handle_, nullptr);
}
