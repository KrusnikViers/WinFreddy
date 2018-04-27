#pragma once

#include "windows.h"

class TrayMenu {
 public:
  explicit TrayMenu(HWND window_handle);
  ~TrayMenu();

  void ShowMenu(int x, int y);
  void SetActiveState(bool is_active);

 private:
  bool is_active_ = true;

  HMENU handle_;
  HWND window_handle_;
};  // class TrayMenu
