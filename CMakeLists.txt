cmake_minimum_required(VERSION 2.8)
project(DiffusionLimitedAlgorithm)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

File(GLOB SOURCES "src/*.cpp")
add_executable(DiffusionLimitedAlgorithm ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(DiffusionLimitedAlgorithm sfml-graphics sfml-window sfml-system)
