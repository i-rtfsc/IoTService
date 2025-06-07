cmake_minimum_required(VERSION 3.16)
project(IoTServiceProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 引入依赖模块
include(cmake/deps.cmake)
# 加载 clang-format 检查模块
#include(${CMAKE_SOURCE_DIR}/cmake/clang_format.cmake)
#include(${CMAKE_SOURCE_DIR}/cmake/clang_tidy.cmake)

# 添加 proto 编译逻辑
add_subdirectory(proto)

# 添加 server 模块
add_subdirectory(source)
