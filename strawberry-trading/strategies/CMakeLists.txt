file(GLOB_RECURSE STRATS_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

file(GLOB_RECURSE STRATS_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp"
)

add_library(strategies STATIC ${STRATS_SOURCES} ${STRATS_HEADERS})

target_link_libraries(strategies PRIVATE core)

target_include_directories(strategies
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)