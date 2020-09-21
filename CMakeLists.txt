cmake_minimum_required(VERSION 2.8)

project(knfancurve)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#qt5_use_modules(test Core Network) # This macro depends from Qt version
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

include_directories(/../knfancurve/knfancurve)

add_executable(${PROJECT_NAME}
    ChartWrapper.cpp
    GPUHelpers.cpp
    GPUStatsModel.cpp
    IntRangeLineEdit.cpp
    MainWindow.cpp
    MiscHelpers.cpp
    GPU.cpp
    SMI.cpp
    SettingsFrame.cpp
    QutieHelpers.cpp
    Main.cpp
    CategoriesWidget.cpp
    ChartsWidget.cpp
    ChartRepainter.cpp
    CategoriesWidget.ui
    ChartWrapper.ui
    ChartsWidget.ui
    MainWindow.ui
    SettingsFrame.ui
    app.qrc
)

target_link_libraries(knfancurve Qt5::Widgets Qt5::Charts)

