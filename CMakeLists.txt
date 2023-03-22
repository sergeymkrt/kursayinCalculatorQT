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
        Sql
        REQUIRED)

add_executable(KursayinCalculator main.cpp Widgets/MainWindow/MainWindow.cpp Widgets/MainWindow/MainWindow.h Core/Src/Calculator.cpp Core/Headers/Calculator.h Core/Src/Number.cpp Core/Headers/Number.h Core/Src/HistoryModel.cpp Core/Headers/HistoryModel.h Core/Headers/HistoryItem.h Core/Headers/HistoryDelegate.h Widgets/Authentication/AuthenticationWidget.cpp Widgets/Authentication/AuthenticationWidget.h Core/Src/UserService.cpp Core/Headers/UserService.h Data/DbManager.cpp Data/DbManager.h Entities/User.h)
target_link_libraries(KursayinCalculator
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        )

