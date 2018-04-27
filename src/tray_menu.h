#pragma once

#include "windows.h"

class TrayMenu {
 public:
  explicit TrayMenu(HWND window_handle);
  ~TrayMenu();

  void ShowMenu(int x, int y);

 private:
  HMENU handle_;
  HWND window_handle_;
};  // class TrayMenu
