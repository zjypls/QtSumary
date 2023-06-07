cmake_minimum_required(VERSION 3.21)

project(lib)

file(GLOB libSrcs *.h *.cpp)

qt_add_library(${PROJECT_NAME} STATIC ${libSrcs})
target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network)
target_compile_definitions(${PROJECT_NAME} PUBLIC Z_SOURCE_DIR)