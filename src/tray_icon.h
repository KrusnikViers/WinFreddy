#pragma once

#include <memory>

#include "windows.h"
#include "winuser.h"

class TrayIcon {
 public:
  TrayIcon(HWND message_window_handle, bool is_active);
  ~TrayIcon();

  void SetActiveIcon(bool is_active);

 private:
  NOTIFYICONDATA current_icon_data_;
  HICON active_icon_;
  HICON rest_icon_;
};  // class TrayIcon
