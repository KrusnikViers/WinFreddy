#pragma once

#include <memory>

#include "windows.h"
#include "winuser.h"

class TrayIcon {
 public:
  TrayIcon(HWND message_window_handle);
  ~TrayIcon();

  // Switches icon state, returns true if updated state is to stay awake.
  bool SwitchState();

 private:
  class ThreadLocker;

  void SetStateInternal(bool state);
  void UpdateIconData();

  std::unique_ptr<ThreadLocker> thread_locker_;
  NOTIFYICONDATA current_icon_data_;
  HICON active_icon_;
  HICON rest_icon_;
};  // class TrayIcon
