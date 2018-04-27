#pragma once

#include "windows.h"

#include "tray_menu.h"

class TrayIcon {
 public:
  explicit TrayIcon(HWND message_window_handle);
  ~TrayIcon();

  void SetActiveState(bool is_active);
  void ShowMenu();

 private:
  NOTIFYICONDATA current_icon_data_;
  HICON active_icon_;
  HICON rest_icon_;
  TrayMenu menu_;
};  // class TrayIcon
