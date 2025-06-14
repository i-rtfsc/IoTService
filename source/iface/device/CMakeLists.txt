# 定义一个只包含头文件的 INTERFACE 库
add_library(iface_device INTERFACE)

# 设置头文件搜索路径（添加 include 目录本身）
target_include_directories(iface_device INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(iface_device
        INTERFACE
        common_headers
        plugin_factory
)
