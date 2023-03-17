cmake_minimum_required(VERSION 3.24)
project(KursayinCalculator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "/Users/sergeymkrtumyan/Qt/6.4.0/macos")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 6)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(KursayinCalculator main.cpp Widgets/MainWindow/MainWindow.cpp Widgets/MainWindow/MainWindow.h Core/Calculator/Calculator.cpp Core/Calculator/Calculator.h Core/Number/Number.cpp Core/Number/Number.h)
target_link_libraries(KursayinCalculator
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )

