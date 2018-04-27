#include "core_window.h"

#include "constants.h"
#include "registry_record.h"
#include "utils.h"

namespace {

const char* kWindowClassName = "WinFreddie_CoreWindow";
const std::string kModuleFileName = GetModuleFilename();

CoreWindow* g_instance = nullptr;

LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM w_param,
                                    LPARAM l_param) {
  CHECK(g_instance);
  return g_instance->WindowProc(hwnd, msg, w_param, l_param);
}

}  // namespace

CoreWindow::CoreWindow() {
  CHECK(!g_instance);
  g_instance = this;

  WNDCLASSEX window_class = {};
  window_class.cbSize = sizeof(window_class);
  window_class.lpfnWndProc = InternalWindowProc;
  window_class.hInstance = GetModuleHandle(nullptr);
  window_class.lpszClassName = kWindowClassName;
  ATOM class_handle = RegisterClassEx(&window_class);
  CHECK(class_handle);
  if (!class_handle) throw std::logic_error(__FUNCTION__);

  window_handle_ = CreateWindowEx(
      0, reinterpret_cast<LPCSTR>(MAKELONG(class_handle, 0)), nullptr, 0, 0, 0,
      0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);
  CHECK(window_handle_);

  if (RegistryRecord(kRegistryMainKey).GetIntValue(kRegistryDefaultState, 1))
    thread_locker_.reset(new ScopedThreadLocker());
  tray_icon_.reset(new TrayIcon(window_handle_, !!thread_locker_));
}

CoreWindow::~CoreWindow() {
  thread_locker_.reset();
  tray_icon_.reset();
  CloseWindow(window_handle_);
  g_instance = nullptr;
}

LRESULT
CoreWindow::WindowProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  if (msg == kIconMessageID) {
    switch (l_param) {
      // Left click on tray icon.
      case WM_LBUTTONUP:
        if (thread_locker_) {
          thread_locker_.reset();
          tray_icon_->SetActiveIcon(false);
          RegistryRecord(kRegistryMainKey).SetValue(kRegistryDefaultState, 0);
        } else {
          thread_locker_.reset(new ScopedThreadLocker());
          tray_icon_->SetActiveIcon(true);
          RegistryRecord(kRegistryMainKey).RemoveValue(kRegistryDefaultState);
        }
        break;

      // Right click on tray icon.
      case WM_RBUTTONUP: {
        POINT cursor_position = {};
        GetCursorPos(&cursor_position);
        tray_icon_->ShowMenu(cursor_position.x, cursor_position.y);
        break;
      }

      default:
        break;
    }
  } else if (msg == WM_COMMAND && !HIWORD(w_param) && !l_param) {
    switch (LOWORD(w_param)) {
      // Autolaunch line clicked in context menu.
      case kAutolaunchItemID: {
        RegistryRecord autolaunch_record(kRegistryAutolaunchKey);
        if (autolaunch_record.GetStringValue(kRegistryAppPath) ==
            kModuleFileName) {
          autolaunch_record.RemoveValue(kRegistryAppPath);
        } else {
          autolaunch_record.SetValue(kRegistryAppPath, kModuleFileName);
        }
        break;
      }

      // About line clicked in context menu.
      case kAboutItemID:
        ShellExecute(nullptr, nullptr,
                     "https://github.com/KrusnikViers/WinFreddie", 0, 0,
                     SW_SHOWNORMAL);
        break;

      // Exit line clicked in context menu.
      case kExitItemID:
        PostQuitMessage(0);
        break;

      default:
        break;
    };
  }
  return DefWindowProc(hwnd, msg, w_param, l_param);
}
