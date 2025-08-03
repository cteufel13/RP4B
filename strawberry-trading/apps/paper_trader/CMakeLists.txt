add_executable(paper_trader main.cpp)

target_link_libraries(paper_trader
    PRIVATE
        api
        scheduler
        logging
        core
        strategies
)