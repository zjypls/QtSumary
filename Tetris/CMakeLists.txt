cmake_minimum_required(VERSION 3.20)


project(Tetris)

file(GLOB srcs *.cpp *.h)

add_executable(${PROJECT_NAME} ${srcs})
target_link_libraries(
        ${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
)