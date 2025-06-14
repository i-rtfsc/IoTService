#include "grpc/IoTServiceImpl.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <thread>

// 日志标签，用于区分日志来源
static constexpr const char* kTAG = "IOT-Server";

/**
 * @brief 启动并运行 gRPC 服务器的函数
 *
 * - 监听 0.0.0.0:50051 地址上的客户端请求
 * - 注册 IoTServiceImpl 服务实例
 * - 启动服务器并阻塞等待，直到服务器关闭
 *
 * @note 此函数会阻塞，直到服务器显式关闭。
 */
void runGrpcServer() {
    // 服务器监听地址和端口
    std::string server_address("0.0.0.0:50051");

    // 创建服务实现对象
    IoTServiceImpl service;

    // 初始化 gRPC 反射插件，允许客户端查询服务信息
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    // gRPC 服务构建器
    grpc::ServerBuilder builder;

    // 添加监听端口，使用不安全的服务器凭据（明文传输）
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // 注册服务实例
    builder.RegisterService(&service);

    // 构建并启动服务器
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    // 打印服务器启动日志
    std::cout << "IoT gRPC server listening on " << server_address << std::endl;

    // 阻塞等待，直到服务器关闭
    server->Wait();
}

/**
 * @brief 程序入口函数
 *
 * - 启动一个独立线程运行 gRPC 服务器
 * - 主线程等待 gRPC 线程结束
 *
 * @param argc 命令行参数数量
 * @param argv 命令行参数数组
 * @return int 程序退出码，通常为0表示正常退出
 */
auto main(int argc, char** argv) -> int {
    // 创建并启动运行gRPC服务器的线程
    std::thread grpcThread(runGrpcServer);

    // 主线程等待gRPC线程执行完毕（一般阻塞直到服务器关闭）
    grpcThread.join();

    // 程序正常退出
    return 0;
}
