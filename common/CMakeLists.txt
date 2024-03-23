add_library(
    QF_Common STATIC
    dvs_widget.h
    dvs_widget.cpp
    dvs_widget.ui
    windowUtils.h
    fileTypes.h
)



include_directories(${Qt6Core_INCLUDE_DIRS})
include_directories(${Qt6Widgets_INCLUDE_DIRS})

target_link_libraries(QF_Common PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets QF_Compression)

target_include_directories(QF_Common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
