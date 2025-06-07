cmake_minimum_required(VERSION 3.16)
project(proto_lib)

# 查找依赖
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# 获取 gRPC 插件路径
get_target_property(GRPC_CPP_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin LOCATION)

# 查找所有 .proto 文件（可递归）
file(GLOB_RECURSE PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

# 设置生成输出目录
set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

# 遍历 .proto 文件生成对应的源文件
set(GENERATED_SRC "")
set(GENERATED_HDR "")
foreach (proto_file ${PROTO_FILES})
    get_filename_component(proto_name ${proto_file} NAME_WE)

    set(proto_src "${GENERATED_DIR}/${proto_name}.pb.cc")
    set(proto_hdr "${GENERATED_DIR}/${proto_name}.pb.h")
    set(grpc_src "${GENERATED_DIR}/${proto_name}.grpc.pb.cc")
    set(grpc_hdr "${GENERATED_DIR}/${proto_name}.grpc.pb.h")

    add_custom_command(
            OUTPUT ${proto_src} ${proto_hdr}
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
            ARGS --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
            --cpp_out=${GENERATED_DIR}
            ${proto_file}
            DEPENDS ${proto_file}
            COMMENT "Generating protobuf code for ${proto_name}.proto"
    )

    add_custom_command(
            OUTPUT ${grpc_src} ${grpc_hdr}
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
            ARGS --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
            --grpc_out=${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
            ${proto_file}
            DEPENDS ${proto_file}
            COMMENT "Generating gRPC code for ${proto_name}.proto"
    )

    list(APPEND GENERATED_SRC ${proto_src} ${grpc_src})
    list(APPEND GENERATED_HDR ${proto_hdr} ${grpc_hdr})
endforeach ()

# 添加生成依赖 target，确保执行
add_custom_target(proto_gen ALL DEPENDS ${GENERATED_SRC} ${GENERATED_HDR})

# 创建静态库
add_library(proto_lib STATIC ${GENERATED_SRC} ${GENERATED_HDR})
add_dependencies(proto_lib proto_gen)

# 包含生成的头文件路径
target_include_directories(proto_lib PUBLIC ${GENERATED_DIR})

# 链接 protobuf 和 gRPC 库
target_link_libraries(proto_lib PUBLIC
        protobuf::libprotobuf
        gRPC::grpc++
)
