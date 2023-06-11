cmake_minimum_required(VERSION 3.24)
project(QVulkan)

file(GLOB srcs *.h *.cpp)
add_executable(${PROJECT_NAME} ${srcs})
target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
