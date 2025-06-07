#pragma once

#include "framework/MessageRouter.h"
#include "iot_service.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class IoTServiceImpl final : public iot::IoTService::Service {
public:
    grpc::Status sendCommand(grpc::ServerContext* context, const iot::DeviceCommand* request,
                             iot::CommandResponse* response) override;

    grpc::Status reportStatus(grpc::ServerContext* context, const iot::DeviceStatus* request,
                              iot::Ack* response) override;

    grpc::Status heartbeat(grpc::ServerContext* context,
                           grpc::ServerReaderWriter<iot::Ack, iot::HeartbeatRequest>* stream) override;

private:
    static constexpr const char* kTAG = "IoTServiceImpl";
    IOT_FRAMEWORK_NS::MessageRouter mMessageRouter = IOT_FRAMEWORK_NS::MessageRouter {};
};
