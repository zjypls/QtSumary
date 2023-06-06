cmake_minimum_required(VERSION 3.21)

project(FileTrans)

file(GLOB srcs *.cpp *.h)

qt_add_executable(${PROJECT_NAME} ${srcs})
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBPATH})
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        lib
)
target_compile_definitions(${PROJECT_NAME} PUBLIC Z_SOURCE_DIR)