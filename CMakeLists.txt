cmake_minimum_required(VERSION 3.19)
project(Clion_OpenGL)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/cpp/main.cpp src/cpp/tgaload.cpp)

set(TEXTURE_PATH "../Clion_OpenGL/src/texture")

include_directories("include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/texture)

add_executable(Clion_OpenGL ${SOURCE_FILES})


target_link_libraries(Clion_OpenGL -lglut -lGL -lGLU -lGLEW -lglfw)

