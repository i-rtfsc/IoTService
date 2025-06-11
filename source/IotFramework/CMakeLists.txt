file(GLOB_RECURSE FRAMEWORK_SOURCES *.h *.cpp)

add_library(IotFramework STATIC ${FRAMEWORK_SOURCES})

add_definitions(-DENABLE_AUTH_MOCK)

target_include_directories(IotFramework
        PUBLIC
        ${PROJECT_SOURCE_DIR}/source/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(IotFramework PUBLIC
        IotUtils
)

target_compile_options(IotFramework PRIVATE -Wall -Wextra -Wpedantic)
