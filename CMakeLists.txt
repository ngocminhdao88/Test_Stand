cmake_minimum_required(VERSION 3.5)

project(Test_Stand LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS SerialBus REQUIRED)
find_package(Qt5 COMPONENTS SerialPort REQUIRED)

if(ANDROID)
  add_library(Test_Stand SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(Test_Stand
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    modbusrtusettingsdialog.cpp
    modbusrtusettingsdialog.h
    modbusrtusettingsdialog.ui
    error.cpp
    error.h
    interfaces/ivfd.h
    interfaces/ilogger.h
    unicovfd.cpp
    unicovfd.h
    fixedpointnumber.cpp
    fixedpointnumber.h
    errorlogger.cpp
    errorlogger.h
  )
endif()

target_link_libraries(Test_Stand PRIVATE Qt5::Widgets)
target_link_libraries(Test_Stand PRIVATE Qt5::SerialBus)
target_link_libraries(Test_Stand PRIVATE Qt5::SerialPort)
