#include "tray_icon.h"

#include "winreg.h"

#include "gen/resources.h"
#include "registry_record.h"

namespace {

const char kCommonRegistryKey[] = "Software\\KrusnikViers\\WinFreddie";
const char kDefaultStateRegistryName[] = "DefaultState";

const char kAwakeTip[] = "Stay awake!";
const char kRestTip[] = "Computer may sleep";

HICON GetIconFromBinary(const unsigned char* data, size_t size) {
  HICON result = nullptr;
  char path_buffer[MAX_PATH + 10] = {};
  char filename_buffer[MAX_PATH + 10] = {};
  if (GetTempPath(MAX_PATH + 10, path_buffer) &&
      GetTempFileName(path_buffer, nullptr, 1, filename_buffer)) {
    FILE* temporary_file = fopen(filename_buffer, "wb");
    fwrite(data, size, 1, temporary_file);
    fclose(temporary_file);
    result = reinterpret_cast<HICON>(
        LoadImage(nullptr, filename_buffer, IMAGE_ICON, 0, 0,
                  LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED));
  }
  return result;
}

}  // namespace

TrayIcon::TrayIcon(HWND message_window_handle) {
  awake_icon_ = GetIconFromBinary(sun_ico, sun_ico_size);
  rest_icon_ = GetIconFromBinary(moon_ico, moon_ico_size);

  current_icon_data_.cbSize = sizeof(current_icon_data_);
  current_icon_data_.hWnd = message_window_handle;
  current_icon_data_.uID = 0;
  current_icon_data_.uFlags = NIF_TIP | NIF_ICON;

  is_awake_state_ =
      RegistryRecord(kCommonRegistryKey, kDefaultStateRegistryName)
          .GetValue(true);
  UpdateIconData();
  Shell_NotifyIcon(NIM_ADD, &current_icon_data_);
}

TrayIcon::~TrayIcon() { Shell_NotifyIcon(NIM_DELETE, &current_icon_data_); }

bool TrayIcon::SwitchState() {
  is_awake_state_ = !is_awake_state_;
  RegistryRecord(kCommonRegistryKey, kDefaultStateRegistryName)
      .SetValue(is_awake_state_);
  UpdateIconData();
  Shell_NotifyIcon(NIM_MODIFY, &current_icon_data_);
  return is_awake_state_;
}

void TrayIcon::UpdateIconData() {
  strcpy(current_icon_data_.szTip, is_awake_state_ ? kAwakeTip : kRestTip);
  current_icon_data_.hIcon = is_awake_state_ ? awake_icon_ : rest_icon_;
}
