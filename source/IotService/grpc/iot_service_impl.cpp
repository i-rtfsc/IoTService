#include "iot_service_impl.h"
#include "utils/Log.h"

extern "C" {
void show_device_info(const char* device_id, const char* message);
}

grpc::Status IoTServiceImpl::sendCommand(grpc::ServerContext* context, const iot::DeviceCommand* request,
                                         iot::CommandResponse* response) {

    show_device_info("solo", "test");

    auto result = mMessageRouter.handleCommand(request->device_id(), request->command(), request->user_id(),
                                               request->auth_token());

    response->set_code(result == "Command accepted" ? 0 : 1);
    response->set_message(result);
    return grpc::Status::OK;
}

grpc::Status IoTServiceImpl::reportStatus(grpc::ServerContext* context, const iot::DeviceStatus* request,
                                          iot::Ack* response) {
    mMessageRouter.handleStatusReport(request->device_id(), request->status(), request->user_id(),
                                      request->auth_token());
    response->set_code(0);
    response->set_message("Status received");
    return grpc::Status::OK;
}

// 基于双向流的心跳实现
grpc::Status IoTServiceImpl::heartbeat(grpc::ServerContext* context,
                                       grpc::ServerReaderWriter<iot::Ack, iot::HeartbeatRequest>* stream) {
    iot::HeartbeatRequest request;
    std::string last_device_id; // 记录最新有效device_id

    while (stream->Read(&request)) {
        last_device_id = request.device_id();
        //        if (context->IsCancelled()) {
        //            mMessageRouter.handleDisconnect(last_device_id);
        //        }

        bool ok = mMessageRouter.handleHeartbeat(request.device_id(), request.user_id(), request.auth_token());

        iot::Ack ack;
        ack.set_code(ok ? 0 : 1);
        ack.set_message(ok ? "Alive" : "Auth failed");

        if (!stream->Write(ack)) {
            break;
        }
    }

    // 读流结束表示客户端断开
    if (!last_device_id.empty()) {
        mMessageRouter.handleDisconnect(last_device_id);
    } else {
        LOGW(kTAG, "heartbeat ended but device_id is empty");
    }

    return grpc::Status::OK;
}
