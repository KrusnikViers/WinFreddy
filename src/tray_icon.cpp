#include "tray_icon.h"

#include "winreg.h"

#include "constants.h"
#include "registry_record.h"

class TrayIcon::ThreadLocker {
 public:
  ThreadLocker() {
    SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
  }

  ~ThreadLocker() { SetThreadExecutionState(ES_CONTINUOUS); }
};  // class ThreadLocker

TrayIcon::TrayIcon(HWND message_window_handle) {
  if (RegistryRecord(kRegistryMainKey).GetIntValue(kRegistryDefaultState, 1))
    thread_locker_.reset(new ThreadLocker());

  active_icon_ = LoadIcon(GetModuleHandle(nullptr), "active");
  rest_icon_ = LoadIcon(GetModuleHandle(nullptr), "rest");
  current_icon_data_.cbSize = sizeof(current_icon_data_);
  current_icon_data_.hWnd = message_window_handle;
  current_icon_data_.uID = 0;
  current_icon_data_.uCallbackMessage = kIconMessageID;
  current_icon_data_.uVersion = NOTIFYICON_VERSION;
  current_icon_data_.uFlags = NIF_TIP | NIF_ICON | NIF_MESSAGE;

  UpdateIconData();
  Shell_NotifyIcon(NIM_ADD, &current_icon_data_);
}

TrayIcon::~TrayIcon() {
  Shell_NotifyIcon(NIM_DELETE, &current_icon_data_);
  DestroyIcon(active_icon_);
  DestroyIcon(rest_icon_);
}

bool TrayIcon::SwitchState() {
  if (thread_locker_) {
    thread_locker_.reset();
    RegistryRecord(kRegistryMainKey).SetValue(kRegistryDefaultState, 0);
  } else {
    thread_locker_.reset(new ThreadLocker());
    RegistryRecord(kRegistryMainKey).RemoveValue(kRegistryDefaultState);
  }

  UpdateIconData();
  Shell_NotifyIcon(NIM_MODIFY, &current_icon_data_);
  return !!thread_locker_;
}

void TrayIcon::UpdateIconData() {
  strcpy(current_icon_data_.szTip,
         thread_locker_ ? kActiveTip.c_str() : kRestTip.c_str());
  current_icon_data_.hIcon = thread_locker_ ? active_icon_ : rest_icon_;
}
