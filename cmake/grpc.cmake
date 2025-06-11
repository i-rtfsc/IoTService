# 支持外部项目
include(FetchContent)

# 可选参数 DL_GRPC，默认 OFF（即优先查找系统 gRPC/protobuf）
option(DL_GRPC "Download gRPC and protobuf from source" OFF)

if (DL_GRPC)
    message(STATUS "DL_GRPC=ON: downloading gRPC and protobuf via FetchContent...")

    # 拉取 gRPC（gRPC 会自动拉取 protobuf 作为子模块）
    FetchContent_Declare(
            grpc
            GIT_REPOSITORY https://github.com/grpc/grpc.git
            GIT_kTAG v1.73.0 # 最新稳定版本
    )
    FetchContent_MakeAvailable(grpc)

else ()
    message(STATUS "DL_GRPC=OFF: using system-installed gRPC and protobuf...")

    find_package(Protobuf REQUIRED)
    find_package(gRPC REQUIRED)

    # 打印 Protobuf 版本
    message(STATUS "Found Protobuf:")
    message(STATUS "  Protobuf_VERSION      = ${Protobuf_VERSION}")
    message(STATUS "  Protobuf_LIBRARIES    = ${Protobuf_LIBRARIES}")
    message(STATUS "  Protobuf_INCLUDE_DIRS = ${Protobuf_INCLUDE_DIRS}")

    # 打印 gRPC 版本
    message(STATUS "Found gRPC:")
    message(STATUS "  gRPC_VERSION               = ${gRPC_VERSION}")
    message(STATUS "  gRPC_CPP_PLUGIN_VERSION    = ${gRPC_CPP_PLUGIN_VERSION}")
    message(STATUS "  gRPC_CPP_PLUGIN_EXECUTABLE = ${gRPC_CPP_PLUGIN_EXECUTABLE}")

endif ()
