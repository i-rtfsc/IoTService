cmake_minimum_required(VERSION 3.16)
project(IoTService LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入依赖模块
include(cmake/grpc.cmake)

# 加载 clang-format 检查模块
include(${CMAKE_SOURCE_DIR}/cmake/clang-format.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang-tidy.cmake)

# 添加 proto 编译逻辑
add_subdirectory(proto)

# 添加 server 模块
add_subdirectory(source)

option(IOT_BUILD_TESTS "enable test" ON)
# 添加测试模块
if (IOT_BUILD_TESTS)
    include(cmake/gtest.cmake)
    add_subdirectory(tests)
endif ()
