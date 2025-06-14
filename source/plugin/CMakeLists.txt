# 定义一个只包含头文件的 INTERFACE 库
add_library(plugin_factory INTERFACE)

# 设置头文件搜索路径（添加 include 目录本身）
target_include_directories(plugin_factory INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
