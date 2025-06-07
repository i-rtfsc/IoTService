file(GLOB_RECURSE UTILS_SOURCES *.h *.cpp)

add_library(IotUtils STATIC ${UTILS_SOURCES})

target_include_directories(IotUtils
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/source/include
)

target_link_libraries(IotUtils)

target_compile_options(IotUtils PRIVATE -Wall -Wextra -Wpedantic)
