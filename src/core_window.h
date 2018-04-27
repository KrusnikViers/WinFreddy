#pragma once

#include <memory>

#include "windows.h"

#include "tray_icon.h"
#include "scoped_thread_locker.h"

class CoreWindow {
 public:
  CoreWindow();
  ~CoreWindow();

  HWND window_handle() const { return window_handle_; }

  LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

 private:
  HWND window_handle_ = nullptr;

  std::unique_ptr<ScopedThreadLocker> thread_locker_;
  std::unique_ptr<TrayIcon> tray_icon_;
};  // class CoreWindow
