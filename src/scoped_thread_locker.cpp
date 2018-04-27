#include "scoped_thread_locker.h"

#include "windows.h"

ScopedThreadLocker::ScopedThreadLocker() {
  SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
}

ScopedThreadLocker::~ScopedThreadLocker() {
  SetThreadExecutionState(ES_CONTINUOUS);
}
