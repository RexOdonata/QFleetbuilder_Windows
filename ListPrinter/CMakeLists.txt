cmake_minimum_required(VERSION 3.14)

project(ListPrinter LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

add_library(ListPrinter STATIC
  ListPrinter_global.h
  qfp_strategycard.cpp
  qfp_strategycard.h
  qfp_strategycard.ui
  NLTemplate.h
  NLTemplate.cpp
  listprinter_legacy.h listprinter_legacy.cpp
  listprinter_short.h listprinter_short.cpp
  listprinter_functions.h listprinter_functions.cpp
  qfp_profilecard.h qfp_profilecard.cpp qfp_profilecard.ui
  qfp_weaponcards.h qfp_weaponcards.cpp qfp_weaponcards.ui
)

target_link_libraries(ListPrinter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport QF_Components ShipView)

target_compile_definitions(ListPrinter PRIVATE SHIPVIEW_LIBRARY)
