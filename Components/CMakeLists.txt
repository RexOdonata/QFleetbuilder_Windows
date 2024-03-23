cmake_minimum_required(VERSION 3.14)

project(QF_Components LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(QF_Components STATIC
  qft_component.h
  qft_enum.h
  qfleet_tonnage.h qfleet_tonnage.cpp
  qfleet_armor.h qfleet_armor.cpp
  qfleet_lock.h qfleet_lock.cpp
  qfleet_arc.h qfleet_arc.cpp
  qfleet_assettype.h qfleet_assettype.cpp
  qfleet_faction.h qfleet_faction.cpp
  qfleet_opttype.h qfleet_opttype.cpp
  qfleet_launchprofile.h qfleet_launchprofile.cpp
  qfleet_weapon.h qfleet_weapon.cpp
  qfleet_option.h qfleet_option.cpp
  qfleet_launchasset.h qfleet_launchasset.cpp
  qfleet_ship.h
  qfleet_ship_shipyard.h qfleet_ship_shipyard.cpp
  qfleet_ship_fleet.h qfleet_ship_fleet.cpp
  qfleet_bgt.h qfleet_bgt.cpp
  qfu_specialrules.h qfu_specialrules.cpp
  qfu_xrulesub.h xrulesub.cpp
  qfleet_statid.h qfleet_statid.cpp
  qfleet_data.h qfleet_data.cpp
)

target_link_libraries(QF_Components PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(QF_Components PRIVATE QF_COMPONENTS_LIBRARY)
