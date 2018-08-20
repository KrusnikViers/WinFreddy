#include "core_window.h"

#include "constants.h"
#include "registry_record.h"
#include "utils.h"

namespace {

CoreWindow* g_instance = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  return g_instance ? g_instance->WindowProc(hwnd, msg, w_param, l_param)
                    : DefWindowProc(hwnd, msg, w_param, l_param);
}

HWND CreateCoreWindow() {
  WNDCLASS window_class = {};
  window_class.lpfnWndProc = WndProc;
  window_class.lpszClassName = "WinFreddyCoreWindow";
  ATOM class_handle = RegisterClass(&window_class);
  CHECK(class_handle);

  HWND handle =
      CreateWindow(reinterpret_cast<LPCSTR>(MAKELONG(class_handle, 0)), nullptr,
                   0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);
  CHECK(handle);
  return handle;
}

}  // namespace

CoreWindow::CoreWindow()
    : window_handle_(CreateCoreWindow()), tray_icon_(window_handle_) {
  CHECK(!g_instance);
  g_instance = this;

  if (RegistryRecord(kRegistryMainKey)
          .GetBoolValue(kRegistryDefaultState, true)) {
    thread_locker_.reset(new ScopedThreadLocker());
  }
  tray_icon_.SetActiveState(!!thread_locker_);
}

CoreWindow::~CoreWindow() {
  CloseWindow(window_handle_);
  g_instance = nullptr;
}

LRESULT
CoreWindow::WindowProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  if (msg == kIconMessageID) {
    switch (l_param) {
      // Left click on tray icon.
      case WM_LBUTTONUP:
        SwitchState();
        break;

      // Right click on tray icon.
      case WM_RBUTTONUP:
        tray_icon_.ShowMenu();
        break;

      default:
        break;
    }
  } else if (msg == WM_COMMAND && !HIWORD(w_param) && !l_param) {
    switch ((MenuID)LOWORD(w_param)) {
      // Autolaunch line clicked in context menu.
      case MenuID::Autolaunch:
        SwitchAutolaunch();
        break;

      // Remain active line clicked in context menu
      case MenuID::RemainActive:
        SwitchState();
        break;

      // About line clicked in context menu.
      case MenuID::About:
        ShellExecute(nullptr, nullptr,
                     "https://github.com/KrusnikViers/WinFreddy", 0, 0,
                     SW_SHOWNORMAL);
        break;

      // Exit line clicked in context menu.
      case MenuID::Exit:
        PostQuitMessage(0);
        break;

      default:
        break;
    };
  } else if (msg == WM_POWERBROADCAST) {
    if (thread_locker_)
      thread_locker_.reset(new ScopedThreadLocker());
  }
  return DefWindowProc(hwnd, msg, w_param, l_param);
}

void CoreWindow::SwitchState() {
  if (thread_locker_) {
    thread_locker_.reset();
    tray_icon_.SetActiveState(false);
    RegistryRecord(kRegistryMainKey).SetValue(kRegistryDefaultState, false);
  } else {
    thread_locker_.reset(new ScopedThreadLocker());
    tray_icon_.SetActiveState(true);
    RegistryRecord(kRegistryMainKey).RemoveValue(kRegistryDefaultState);
  }
}

void CoreWindow::SwitchAutolaunch() {
  RegistryRecord autolaunch_record(kRegistryAutolaunchKey);
  if (autolaunch_record.GetStringValue(kRegistryAppPath) == kModuleFileName)
    autolaunch_record.RemoveValue(kRegistryAppPath);
  else
    autolaunch_record.SetValue(kRegistryAppPath, kModuleFileName);
}
