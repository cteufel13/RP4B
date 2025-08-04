cmake_minimum_required(VERSION 4.0.3)
project(strawberry-trading LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(CURL REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)


add_subdirectory(logging)
add_subdirectory(api)
add_subdirectory(core)
add_subdirectory(scheduler)
add_subdirectory(strategies)
add_subdirectory(apps) 