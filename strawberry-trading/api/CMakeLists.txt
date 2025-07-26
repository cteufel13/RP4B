file(GLOB_RECURSE API_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

file(GLOB_RECURSE API_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp"
)

add_library(api STATIC ${API_SOURCES} ${API_HEADERS})

target_include_directories(api
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(api PRIVATE CURL::libcurl)
target_link_libraries(api PRIVATE nlohmann_json::nlohmann_json )
