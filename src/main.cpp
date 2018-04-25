#include "message_window.h"

int main() {
  MessageWindow window;

  MSG message;
  while (BOOL result = GetMessage(&message, window.window_handle(), 0, 0)) {
    if (result != -1) {
      TranslateMessage(&message);
      DispatchMessage(&message);
    }
  }

  return 0;
}
