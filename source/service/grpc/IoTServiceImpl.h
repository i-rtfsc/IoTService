#pragma once

#include "MessageRouter.h"
#include "iot_service.grpc.pb.h"
#include <grpcpp/grpcpp.h>

/**
 * @brief IoT 服务的具体实现类，继承自 gRPC 自动生成的服务基类 iot::IoTService::Service。
 *
 * 该类实现了设备命令发送、状态上报和心跳通信的 RPC 接口，负责处理客户端请求，
 * 并通过内部的消息路由器（MessageRouter）进行业务逻辑分发和处理。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class IoTServiceImpl final : public iot::IoTService::Service {
public:
    /**
     * @brief 发送设备命令接口
     *
     * 接收来自客户端的设备命令请求，并处理该命令，最终将处理结果写入响应对象。
     *
     * @param context gRPC 服务上下文，包含调用相关信息
     * @param request 客户端传入的设备命令请求
     * @param response 服务器填充的命令执行响应
     * @return grpc::Status 返回 RPC 调用的状态，指示请求是否成功处理
     */
    auto sendCommand(grpc::ServerContext* context, const iot::DeviceCommand* request,
                     iot::CommandResponse* response) -> grpc::Status override;

    /**
     * @brief 设备状态上报接口
     *
     * 设备向服务器上报当前状态，服务器确认接收后返回应答。
     *
     * @param context gRPC 服务上下文，包含调用相关信息
     * @param request 客户端传入的设备状态信息
     * @param response 服务器发送的确认应答
     * @return grpc::Status 返回 RPC 调用的状态，指示请求是否成功处理
     */
    auto reportStatus(grpc::ServerContext* context, const iot::DeviceStatus* request,
                      iot::Ack* response) -> grpc::Status override;

    /**
     * @brief 双向流心跳通信接口
     *
     * 支持设备与服务器之间的双向流通信，客户端不断发送心跳请求，服务器返回确认，
     * 用于保持连接活跃和状态同步。
     *
     * @param context gRPC 服务上下文，包含调用相关信息
     * @param stream 双向流读写对象，用于接收心跳请求并发送确认响应
     * @return grpc::Status 返回 RPC 调用的状态，指示流是否正常结束
     */
    auto heartbeat(grpc::ServerContext* context,
                   grpc::ServerReaderWriter<iot::Ack, iot::HeartbeatRequest>* stream) -> grpc::Status override;

private:
    static constexpr const char* kTAG = "IoTServiceImpl";            // 日志标识符，用于日志输出
    IOT_NS::MessageRouter mMessageRouter = IOT_NS::MessageRouter {}; // 内部消息路由器，负责业务消息分发
};
