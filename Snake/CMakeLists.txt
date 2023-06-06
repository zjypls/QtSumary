cmake_minimum_required(VERSION 3.25)
project(Snake)


add_executable(${PROJECT_NAME} main.cpp zWidget.h zWidget.cpp Snake.h Snake.cpp)
target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
target_compile_definitions(${PROJECT_NAME} PUBLIC Z_SOURCE_DIR)
