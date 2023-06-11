#build with clion
cmake_minimum_required(VERSION 3.20)
project(Sumary)
set(CMAKE_CXX_STANDARD 17 REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(LIBPATH ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#set Qt6 path
set(CMAKE_PREFIX_PATH "C:/Qt/6.3.0/mingw_64/lib/cmake")
add_compile_definitions(Z_SOURCE_DIR="${CMAKE_SOURCE_DIR}/")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)
add_subdirectory(lib)
add_subdirectory(Snake)
add_subdirectory(FileSend)
add_subdirectory(QVulkan)
add_subdirectory(MediaPlayer)
add_subdirectory(Tetris)


