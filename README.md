# IOTService

## 项目简介

IoTService 是一个通用、跨平台、设备间自由通信的“万物互联”系统。系统基于 gRPC + ProtoBuf 通信协议设计，支持异构设备（如手机、汽车、智能设备、PC
等）以统一的接口进行注册、发现、消息传输与任务分发。

特点包括：

- 支持多语言接入（C++、Java、Rust 等）
- 支持多终端形态（Android、嵌入式、桌面）
- 支持点对点通信与中心式中转通信
- 提供调试与测试工具（Python、Shell 脚本）

## 项目目录结构

当前只是第一次提交的代码，目录结构会有变动。

```bash

├── CMakeLists.txt               # 顶层构建文件
├── README.md                    # 项目说明
├── client                       # 客户端目录
│   └── tools/python             # Python 调试客户端
│       ├── build_proto.sh       # proto 编译脚本
│       ├── grpc_client.py       # 通用 gRPC 客户端逻辑
│       ├── account_service_pb2.py / _grpc.py
│       ├── iot_service_pb2.py / _grpc.py
├── cmake                        # 构建配置文件
│   ├── clang-format.cmake       # 代码格式化支持
│   ├── clang-tidy.cmake         # 代码静态检查支持
│   └── grpc.cmake               # 依赖下载与管理
├── docs                         # 项目文档
│   ├── clang-tidy-check.md
│   ├── commit-msg.md
│   └── deps.md
├── proto                        # ProtoBuf 定义
│   ├── account_service.proto
│   └── iot_service.proto
├── scripts                      # 通用脚本
│   ├── git-hooks                # 提交规范钩子
│   ├── install-hooks.sh         # 安装钩子脚本
│   └── run-clang-tidy-check.sh  # 一键运行静态检查
└── source                       # 源码目录
    ├── IotFramework             # 框架核心逻辑
    │   ├── device               # 设备管理模块
    │   ├── message              # 消息路由与调度
    │   ├── thread               # 多线程调度结构
    │   ├── user                 # 用户信息管理
    │   └── include/framework    # 公共头文件
    ├── IotService               # 服务端主逻辑
    │   ├── grpc                 # gRPC 服务实现
    │   ├── display              # Rust UI 端展示（WIP）
    │   └── main.cpp             # 入口主函数
    ├── IotUtils                 # 工具库
    │   └── Logger/Log.h         # 日志工具
    └── include/common           # 通用数据结构等

```

## 模块说明

### 通信协议定义（proto）

使用 Protocol Buffers 描述各类设备、服务的数据格式和通信接口。

- account_service.proto：账号服务，负责身份注册与认证
- iot_service.proto：设备注册、上下线通知、消息中转等核心通信接口

生成的 .pb2 / .pb.h 文件用于支持多语言接入。

### 核心通信框架（IotFramework）

用于构建设备间的消息通路与通信调度。模块包括：

- device：设备生命周期管理
- user：用户上下文管理
- message：消息的路由转发逻辑（P2P / 广播等）
- thread：任务线程池、队列、处理器结构体封装
- include/framework：对外暴露的接口头文件

### 服务端实现（IotService）

服务端作为通信的中心或路由节点运行，负责处理 gRPC 请求、协调设备间消息。

- grpc：C++ 端的服务实现（如 IotServiceImpl）
- display：基于 Rust 构建的可视化展示 UI（初步设计）
- main.cpp：gRPC 服务注册和运行主流程

### 工具库（IotUtils）

提供通用工具函数和数据结构。

### 客户端工具与脚本（client）

用于设备接入、调试或轻量服务。

- tools/python：提供通过 Python gRPC 客户端实现测试与模拟发送
- 后续计划加入 android/、car/、home_device/ 等设备子目录

## 多语言接入规划

| 语言             | 接入形式                    | 状态        |
|----------------|-------------------------|-----------|
| C++            | Server / Framework 核心逻辑 | ✅ 已实现（初版） |
| Rust           | UI 展示端 / 轻量设备服务端        | 🔄 开发中    |
| Python         | 调试客户端                   | ✅ 已支持     |
| Java / Android | 移动端客户端（如 phone/car）     | 🕐 计划中    |
| Shell          | 简单调试与自动测试               | ✅ 脚本初步就绪  |

## 依赖管理

参考 [docs/deps.md](docs/deps.md) 文档。

## 构建与调试

### 构建（C++）

```bash

mkdir build && cd build
cmake ..
make -j$(nproc)

```

运行服务端：

```bash

./source/IotService/IotService

```

### 调试（Python）

```bash

cd client/tools/python
# 编译 proto 文件
./build_proto.sh

# 运行 gRPC 客户端
python grpc_client.py

```

## 开发规划

未来扩展方向：

- 支持服务发现和动态设备注册（Zeroconf / Consul 等）
- 引入加密认证机制（如 mTLS / JWT）
- 加入消息可靠性机制（重发、ACK 等）
- Rust 端支持更多协议绑定
- Android 端使用 Java/Kotlin gRPC 客户端对接
- 扩展更多设备类型（如 IoT 传感器、智能家居等）

## Git 提交流程约束

所有提交需要：符合 commit-msg 格式，强制使用 feat:、fix:、refactor: 等前缀

参考 [docs/commit-msg.md](docs/commit-msg.md) 文档。
