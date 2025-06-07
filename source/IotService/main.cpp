#include "grpc/iot_service_impl.h"
#include "utils/Log.h"

#include <grpcpp/grpcpp.h>
#include <thread>

static constexpr const char* kTAG = "IOT-Server";

void runGrpcServer() {
    std::string server_address("0.0.0.0:50051");
    IoTServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    LOGI(kTAG, "IoT gRPC server listening on %s", server_address.c_str());
    server->Wait(); // 阻塞直到 gRPC 退出
}

int main(int argc, char** argv) {
    std::thread grpcThread(runGrpcServer);

    grpcThread.join();

    return 0;
}
