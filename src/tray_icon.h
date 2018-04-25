#pragma once

#include "windows.h"
#include "winuser.h"

class TrayIcon {
public:
    TrayIcon(HWND message_window_handle);
    ~TrayIcon();

    // Switches icon state, returns true if updated state is to stay awake.
    bool SwitchState();

private:
    void UpdateIconData();

    bool is_awake_state_ = true;
    NOTIFYICONDATA current_icon_data_;
    HICON awake_icon_;
    HICON rest_icon_;
};  // class TrayIcon
