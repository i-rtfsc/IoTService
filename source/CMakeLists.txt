# 公共头文件
add_subdirectory(common)

# utils模块：提供通用的工具函数和类
add_subdirectory(utils)

# plugin模块：提供注册 + 工厂 + 链接器 保活机制（无需 dlopen）的通用机制
add_subdirectory(plugin)

# 添加thread模块：提供线程相关的功能
add_subdirectory(core/thread)

# 添加message模块：提供消息定义和处理
add_subdirectory(core/message)

# 添加device接口和实现模块
add_subdirectory(iface/device)
add_subdirectory(impls/device/default)

# 添加user接口和实现模块
add_subdirectory(iface/user)
add_subdirectory(impls/user/default)

# gGRPC 服务
add_subdirectory(service)