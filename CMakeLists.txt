cmake_minimum_required(VERSION 3.5)

project(QFleet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)


add_subdirectory(Components)
add_subdirectory(ListParts)
add_subdirectory(common)
add_subdirectory(ShipView)
add_subdirectory(ListPrinter)
add_subdirectory(compression)
add_subdirectory(Fleetbuilder)
