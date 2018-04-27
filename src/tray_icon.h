#pragma once

#include <memory>

#include "windows.h"
#include "winuser.h"

#include "tray_menu.h"

class TrayIcon {
 public:
  TrayIcon(HWND message_window_handle);
  ~TrayIcon();

  void SetActiveState(bool is_active);
  void ShowMenu(int x, int y);

 private:
  NOTIFYICONDATA current_icon_data_;
  HICON active_icon_;
  HICON rest_icon_;
  TrayMenu menu_;
};  // class TrayIcon
