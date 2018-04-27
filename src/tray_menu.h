#pragma once

#include "windows.h"

class TrayMenu {
 public:
  explicit TrayMenu(HWND window_handle);
  ~TrayMenu();

  void SetActiveState(bool is_active);
  void ShowMenu();

 private:
  bool is_active_ = true;

  HMENU handle_;
  HWND window_handle_;
};  // class TrayMenu
