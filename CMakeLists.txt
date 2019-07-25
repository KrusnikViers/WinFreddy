cmake_minimum_required(VERSION 3.3)
project(WinFreddy)

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
    src/tray_icon.cpp
    src/tray_icon.h
    src/tray_menu.cpp
    src/tray_menu.h
    src/utils.h
)
add_executable(WinFreddy WIN32 ${SOURCES})

target_include_directories(WinFreddy PUBLIC src)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(WinFreddy PRIVATE -Wall -Wextra -Werror )
    set_target_properties(WinFreddy PROPERTIES LINK_FLAGS "-mwindows -static")
elseif(MSVC)
    target_compile_options(WinFreddy PRIVATE -W4 -WX)
    target_compile_definitions(WinFreddy PRIVATE _CRT_SECURE_NO_WARNINGS)
    set_target_properties(WinFreddy PROPERTIES LINK_FLAGS "/subsystem:windows /entry:mainCRTStartup")
endif()
