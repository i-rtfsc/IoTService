# 纯头文件模块
add_library(task_thread INTERFACE)

target_include_directories(task_thread INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 如果 thread 下依赖 common
target_link_libraries(task_thread INTERFACE common_headers)
