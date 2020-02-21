cmake_minimum_required(VERSION 3.5)

project(cockpit LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(cockpit
  main.cpp
  widget.cpp
  widget.h
  widget.ui
)

target_link_libraries(cockpit PRIVATE Qt5::Widgets)
