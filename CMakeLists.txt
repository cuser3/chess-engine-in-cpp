cmake_minimum_required(VERSION 3.10.0)
project(chessengine VERSION 0.1.0 LANGUAGES C CXX)

set(SFML_DIR "D:\\Libraries\\SFML-3.0.0\\lib\\cmake\\SFML")
set(SFML_INCLUDE_DIR "D:\\Libraries\\SFML-3.0.0\\include")
set(SFML_LIBRARY_DIR "D:\\Libraries\\SFML-3.0.0\\lib")

find_package(SFML 3 COMPONENTS Graphics Window System)

add_executable(chessengine main.cpp chessengine.cpp)

target_link_libraries(chessengine PRIVATE SFML::Graphics SFML::Window SFML::System)

include(CTest)
enable_testing()

