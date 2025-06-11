
## grpcurl 使用指南

grpcurl 是一个类似于 curl 的命令行工具，用于调试 gRPC 服务。你要使用 grpcurl 命令，需要先安装 grpcurl 工具。

### 安装方式

```bash

brew install grpcurl

```

### 调用 gRPC 服务

```bash

grpcurl -plaintext localhost:50051 list

```

该命令会列出端口 50051 上的所有 gRPC 服务（前提是服务运行中）。

如需调用具体接口，也可用如下命令：

```bash

grpcurl -plaintext localhost:50051 <ServiceName>/<Method>

```

##

参考 `client/tools/grpcurl` 

```bash

# 调用 sendCommand 方法
./grpcurl_client.sh send

# 调用 reportStatus 方法
./grpcurl_client.sh report

# 查看服务列表
./grpcurl_client.sh list

# 查看 IoTService 接口详情
./grpcurl_client.sh describe

```