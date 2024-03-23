cmake_minimum_required(VERSION 3.5)

project(Fleetbuilder VERSION 0.1 LANGUAGES CXX)

# this is where it all comes together

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui       
        optselect.h optselect.cpp optselect.ui
        shipselect.h shipselect.cpp shipselect.ui
        initlistdialog.h initlistdialog.cpp initlistdialog.ui
        qflw_list.h qflw_list.cpp qflw_list.ui
        qflw_battlegroup.h qflw_battlegroup.cpp qflw_battlegroup.ui
        qflw_group.h qflw_group.cpp qflw_group.ui
        limitwidget.h limitwidget.cpp limitwidget.ui
        shipviewdialog.h shipviewdialog.cpp shipviewdialog.ui
        admiralselectdialog.h admiralselectdialog.cpp admiralselectdialog.ui
        confirmdialog.h confirmdialog.cpp confirmdialog.ui
        rsc/icons.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QFleetbuilder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Fleetbuilder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QFleetbuilder SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QFleetbuilder
            ${PROJECT_SOURCES}
        )
    endif()
endif()

qt_add_resources(QFleetbuilder "resources" PREFIX "/rsc" FILES dfc.jpeg)

target_link_libraries(QFleetbuilder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    QF_Components QF_Common QF_ListParts ShipView ListPrinter QF_Compression)

set_target_properties(QFleetbuilder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QFleetbuilder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QFleetbuilder)
endif()
