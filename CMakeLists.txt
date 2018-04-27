cmake_minimum_required(VERSION 3.3)
project(WinFreddie)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX_STANDARD_REQUIRED TRUE)

set(SOURCES
    src/constants.cpp
    src/constants.h
    src/core_window.cpp
    src/core_window.h
    src/main.cpp
    src/registry_record.cpp
    src/registry_record.h
    src/resources/resources.rc
    src/scoped_thread_locker.cpp
    src/scoped_thread_locker.h
    src/tray_icon.cpp
    src/tray_icon.h
    src/tray_menu.cpp
    src/tray_menu.h
    src/utils.h
)
add_executable(WinFreddie ${SOURCES})

target_include_directories(WinFreddie PUBLIC src)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(WinFreddie PRIVATE -Wall -Wextra -Werror )
elseif(MSVC)
    target_compile_options(WinFreddie PRIVATE -W4 -WX)
    target_compile_definitions(WinFreddie PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
