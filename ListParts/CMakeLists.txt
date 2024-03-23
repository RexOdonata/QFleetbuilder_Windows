cmake_minimum_required(VERSION 3.14)

project(QF_ListParts LANGUAGES CXX)

# These objects are components that are intended to save/load lists

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(QF_ListParts STATIC
  qfleet_cost.h qfleet_cost.cpp
  qfleet_group.h qfleet_group.cpp
  qfleet_battlegroup.h qfleet_battlegroup.cpp
  qfleet_list.h qfleet_list.cpp
)

target_link_libraries(QF_ListParts PRIVATE Qt${QT_VERSION_MAJOR}::Core QF_Components)

target_compile_definitions(QF_ListParts PRIVATE QF_LISTPARTS_LIBRARY)
