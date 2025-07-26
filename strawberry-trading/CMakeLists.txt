cmake_minimum_required(VERSION 4.0.3)
project(strawberry-trading LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(CURL REQUIRED)
find_package(nlohmann_json 3.12.0 REQUIRED)


add_subdirectory(api)
add_subdirectory(apps)

