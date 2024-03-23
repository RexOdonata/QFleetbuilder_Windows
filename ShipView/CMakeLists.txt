cmake_minimum_required(VERSION 3.14)

project(ShipView LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(ShipView STATIC
  ShipView_global.h
  shipview.cpp
  shipview.h
  shipview.ui
)

target_link_libraries(ShipView PRIVATE Qt${QT_VERSION_MAJOR}::Widgets QF_Components)

target_compile_definitions(ShipView PRIVATE SHIPVIEW_LIBRARY)
