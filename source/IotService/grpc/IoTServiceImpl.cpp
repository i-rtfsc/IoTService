#include "IoTServiceImpl.h"
#include "utils/Log.h"

extern "C" {
void show_device_info(const char* device_id, const char* message);
}

/**
 * @brief 处理发送设备命令的 RPC 调用
 *
 * 调用内部消息路由器处理设备命令请求，返回执行结果。
 * 并调用外部C函数打印设备信息用于调试。
 *
 * @param context gRPC 服务上下文
 * @param request 包含设备ID、命令、用户ID、认证Token的命令请求
 * @param response 返回命令执行结果代码及信息
 * @return grpc::Status 返回RPC调用的状态，始终为 OK
 */
auto IoTServiceImpl::sendCommand(grpc::ServerContext* context, const iot::DeviceCommand* request,
                                 iot::CommandResponse* response) -> grpc::Status {
    // 调用外部C函数打印调试信息
    show_device_info("solo", "tests");

    // 通过消息路由器处理命令，获取处理结果字符串
    auto result = mMessageRouter.handleCommand(request->device_id(), request->command(), request->user_id(),
                                               request->auth_token());

    // 根据处理结果设置响应code，"Command accepted"视为成功，code=0，否则code=1
    response->set_code(result == "Command accepted" ? 0 : 1);
    response->set_message(result);

    return grpc::Status::OK;
}

/**
 * @brief 处理设备状态上报的 RPC 调用
 *
 * 通过消息路由器处理状态上报请求，并返回确认应答。
 *
 * @param context gRPC 服务上下文
 * @param request 包含设备ID、状态、用户ID、认证Token的状态请求
 * @param response 返回确认应答，code固定为0表示成功
 * @return grpc::Status 返回RPC调用状态，始终为 OK
 */
auto IoTServiceImpl::reportStatus(grpc::ServerContext* context, const iot::DeviceStatus* request,
                                  iot::Ack* response) -> grpc::Status {
    // 交由消息路由器处理状态上报
    mMessageRouter.handleStatusReport(request->device_id(), request->status(), request->user_id(),
                                      request->auth_token());

    // 设置响应码和消息，表示状态已成功接收
    response->set_code(0);
    response->set_message("Status received");

    return grpc::Status::OK;
}

/**
 * @brief 基于双向流的心跳通信实现
 *
 * 持续读取客户端发送的心跳请求，调用消息路由器处理心跳验证，
 * 并发送相应的确认消息。若客户端断开连接，调用断开处理。
 *
 * @param context gRPC 服务上下文
 * @param stream 双向流读写对象，用于接收心跳请求并发送确认
 * @return grpc::Status 返回RPC调用状态，表示流结束
 */
auto IoTServiceImpl::heartbeat(grpc::ServerContext* context,
                               grpc::ServerReaderWriter<iot::Ack, iot::HeartbeatRequest>* stream) -> grpc::Status {
    iot::HeartbeatRequest request;
    std::string last_device_id; // 记录最后一个有效的设备ID，用于断开处理

    // 持续读取流中的心跳请求
    while (stream->Read(&request)) {
        last_device_id = request.device_id();

        // 调用消息路由器处理心跳请求，返回是否验证成功
        bool ok = mMessageRouter.handleHeartbeat(request.device_id(), request.user_id(), request.auth_token());

        // 构造应答，code为0表示成功，1表示认证失败
        iot::Ack ack;
        ack.set_code(ok ? 0 : 1);
        ack.set_message(ok ? "Alive" : "Auth failed");

        // 向客户端写入应答，如果写失败则退出循环
        if (!stream->Write(ack)) {
            break;
        }
    }

    // 流结束表示客户端断开，调用断开处理
    if (!last_device_id.empty()) {
        mMessageRouter.handleDisconnect(last_device_id);
    } else {
        // 设备ID为空时记录警告日志
        LOGW(kTAG, "heartbeat ended but device_id is empty");
    }

    return grpc::Status::OK;
}
