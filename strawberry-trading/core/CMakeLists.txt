file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp"
)

add_library(core STATIC ${CORE_SOURCES} ${CORE_HEADERS})

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/logging/include
        ${CMAKE_SOURCE_DIR}/api/include
        $<TARGET_PROPERTY:nlohmann_json::nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>

)

target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)
