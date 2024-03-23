cmake_minimum_required(VERSION 3.14)

add_subdirectory(LZ4)

project(QF_Compression LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(
    QF_Compression  STATIC
    compressor.h
    compressor.cpp
    decompressor.h
    decompressor.cpp
    constants.h
)

include_directories(${Qt6Core_INCLUDE_DIRS})

target_link_libraries(QF_Compression PRIVATE Qt${QT_VERSION_MAJOR}::Core LZ4)

target_include_directories(QF_Compression  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
