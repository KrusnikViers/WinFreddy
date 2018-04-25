#include "message_window.h"

namespace {

const char* kWindowClassName = "WinFreddieMessageWindow";

MessageWindow* g_instance = nullptr;

LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT msg, WPARAM w_param,
                                    LPARAM l_param) {
  if (!g_instance) throw std::logic_error(__FUNCTION__);
  return g_instance->WindowProc(hwnd, msg, w_param, l_param);
}

}  // namespace

MessageWindow::MessageWindow() {
  if (g_instance) throw std::logic_error(__FUNCTION__);
  g_instance = this;

  WNDCLASSEX window_class;
  memset(&window_class, 0, sizeof(window_class));
  window_class.cbSize = sizeof(window_class);
  window_class.lpfnWndProc = InternalWindowProc;
  window_class.hInstance = GetModuleHandle(nullptr);
  window_class.lpszClassName = kWindowClassName;
  ATOM class_handle = RegisterClassEx(&window_class);
  if (!class_handle) throw std::logic_error(__FUNCTION__);

  window_handle_ = CreateWindowEx(
      0, reinterpret_cast<LPCSTR>(MAKELONG(class_handle, 0)), nullptr, 0, 0, 0,
      0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);
  if (!window_handle_) throw std::logic_error(__FUNCTION__);

  tray_icon_ptr_.reset(new TrayIcon(window_handle_));
}

MessageWindow::~MessageWindow() {
  tray_icon_ptr_.reset();
  CloseWindow(window_handle_);
  g_instance = nullptr;
}

LRESULT MessageWindow::WindowProc(HWND hwnd, UINT msg, WPARAM w_param,
                                  LPARAM l_param) {
  return DefWindowProc(hwnd, msg, w_param, l_param);
}
