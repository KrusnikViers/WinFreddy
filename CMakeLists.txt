cmake_minimum_required(VERSION 3.3)
project(WinFreddie)
include(cmake/utils.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CXX_STANDARD_REQUIRED TRUE)

make_embedded_resources(${CMAKE_CURRENT_SOURCE_DIR}/src/resources
                        ${CMAKE_CURRENT_SOURCE_DIR}/src/gen/resources)
set(SOURCES
    src/main.cpp
    src/tray_icon.cpp
    src/tray_icon.h
    src/constants.cpp
    src/constants.h
    src/registry_record.cpp
    src/registry_record.h
    src/message_window.cpp
    src/message_window.h
    src/gen/resources.h
    src/gen/resources.cpp
)

add_executable(WinFreddie ${SOURCES})
target_include_directories(WinFreddie PUBLIC src)
set_target_strict_compilation_params(WinFreddie)
