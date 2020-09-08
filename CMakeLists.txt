cmake_minimum_required(VERSION 3.17)
project(convolution)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
file(GLOB_RECURSE fileCollection "src/*.cpp")
add_executable(${PROJECT_NAME} ${fileCollection} src/Document.cpp src/Document.h src/CSVWriter.cpp src/CSVWriter.h)
