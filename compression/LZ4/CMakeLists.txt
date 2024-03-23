project(LZ4 LANGUAGES C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


add_library(
    LZ4 STATIC
    lz4.c
    lz4.h
    lz4file.h
    lz4file.c
    lz4frame.h
    lz4frame.c
    lz4frame_static.h
    lz4hc.h
    lz4hc.c
    xxhash.h
    xxhash.c
)

target_include_directories(LZ4 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
