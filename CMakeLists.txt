cmake_minimum_required(VERSION 3.5)

project(untitled LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets Multimedia MultimediaWidgets REQUIRED)

add_executable(untitled main.cpp)

target_link_libraries(untitled PRIVATE Qt6::Core Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets)

set_target_properties(untitled PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)


install(TARGETS untitled
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
