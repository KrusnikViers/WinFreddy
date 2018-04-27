#include "tray_icon.h"

#include "winreg.h"

#include "constants.h"
#include "registry_record.h"

TrayIcon::TrayIcon(HWND message_window_handle, bool is_active)
    : menu_(message_window_handle) {
  current_icon_data_.cbSize = sizeof(current_icon_data_);
  current_icon_data_.hWnd = message_window_handle;
  current_icon_data_.uID = 0;
  current_icon_data_.uCallbackMessage = kIconMessageID;
  current_icon_data_.uVersion = NOTIFYICON_VERSION;
  current_icon_data_.uFlags = NIF_MESSAGE;
  Shell_NotifyIcon(NIM_ADD, &current_icon_data_);

  active_icon_ = LoadIcon(GetModuleHandle(nullptr), "active");
  rest_icon_ = LoadIcon(GetModuleHandle(nullptr), "rest");
  SetActiveIcon(is_active);
}

TrayIcon::~TrayIcon() {
  Shell_NotifyIcon(NIM_DELETE, &current_icon_data_);
  DestroyIcon(active_icon_);
  DestroyIcon(rest_icon_);
}

void TrayIcon::SetActiveIcon(bool is_active) {
  current_icon_data_.uFlags = current_icon_data_.uFlags | NIF_TIP | NIF_ICON;
  strcpy(current_icon_data_.szTip,
         is_active ? kActiveTip.c_str() : kRestTip.c_str());
  current_icon_data_.hIcon = is_active ? active_icon_ : rest_icon_;
  Shell_NotifyIcon(NIM_MODIFY, &current_icon_data_);
}

void TrayIcon::ShowMenu(int x, int y) {
  menu_.ShowMenu(x, y);
}
