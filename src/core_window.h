#pragma once

#include <memory>

#include "windows.h"

#include "scoped_thread_locker.h"
#include "tray_icon.h"

class CoreWindow {
 public:
  CoreWindow();
  ~CoreWindow();

  HWND window_handle() const { return window_handle_; }

  LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

 private:
  void SwitchState();

  HWND window_handle_ = nullptr;

  TrayIcon tray_icon_;
  std::unique_ptr<ScopedThreadLocker> thread_locker_;
};  // class CoreWindow
