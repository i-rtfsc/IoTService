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
            GIT_kTAG v1.69.0 # 最新稳定版本
    )
    FetchContent_MakeAvailable(grpc)

else ()
    message(STATUS "DL_GRPC=OFF: using system-installed gRPC and protobuf...")

    set(Protobuf_ROOT "/usr/local/opt/protobuf@21") 

    find_package(Protobuf REQUIRED)
    set(Protobuf_LIBRARIES "/usr/local/opt/protobuf@21/lib/libprotobuf.dylib")

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

    #    execute_process(
    #            COMMAND protoc --version
    #            OUTPUT_VARIABLE PROTOC_VERSION
    #            OUTPUT_STRIP_TRAILING_WHITESPACE
    #    )
    #    message(STATUS "protoc version: ${PROTOC_VERSION}")
    #
    #    execute_process(
    #            COMMAND ${gRPC_CPP_PLUGIN_EXECUTABLE} --version
    #            OUTPUT_VARIABLE GRPC_PLUGIN_VERSION
    #            OUTPUT_STRIP_TRAILING_WHITESPACE
    #    )
    #    message(STATUS "gRPC plugin version: ${GRPC_PLUGIN_VERSION}")
    #
endif ()
