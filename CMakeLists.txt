cmake_minimum_required(VERSION 3.10.0)
project(chessengine VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        3.0.0  
)

FetchContent_MakeAvailable(SFML)

add_executable(chessengine main.cpp chessengine.cpp)

target_link_libraries(chessengine PRIVATE SFML::Graphics SFML::Window SFML::System)

# Copy assets to build directory (Debug/Release)
set(IMAGES_SRC_DIR "${CMAKE_SOURCE_DIR}/assets/images")
set(IMAGES_DST_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/assets")


add_custom_command(TARGET chessengine POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${IMAGES_SRC_DIR}"
  "${IMAGES_DST_DIR}"
)

# Copy DLLs to build directory (Debug/Release)
set(DLL_SRC_DIR "${CMAKE_SOURCE_DIR}/assets/dll")
set(DLL_DST_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")

add_custom_command(TARGET chessengine POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${DLL_SRC_DIR}"
  "${DLL_DST_DIR}"
)

include(CTest)
enable_testing()

