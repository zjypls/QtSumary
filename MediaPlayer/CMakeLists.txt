cmake_minimum_required(VERSION 3.20)
project(MediaPlayer)

file(GLOB srcs *.h *.cpp)
find_package(Qt6 COMPONENTS Multimedia MultimediaWidgets REQUIRED)
add_executable(${PROJECT_NAME} ${srcs})
target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        Qt::MultimediaWidgets
        )
target_compile_definitions(${PROJECT_NAME} PUBLIC Z_SOURCE_DIR)
