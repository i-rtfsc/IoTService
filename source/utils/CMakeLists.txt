add_library(utils INTERFACE)

target_include_directories(utils INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(utils INTERFACE common_headers)
