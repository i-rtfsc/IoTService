# 在顶层定义，供子目录使用
set(RUST_CRATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/display)
set(RUST_TARGET_DIR ${RUST_CRATE_DIR}/target)
set(RUST_LIB_NAME display)

add_subdirectory(display)

# 后续定义
add_executable(iot_service
        main.cpp
        grpc/IoTServiceImpl.cpp
)

target_include_directories(iot_service
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(iot_service PRIVATE
        common_headers
        plugin_factory
        task_thread
        message_router
        iface_user
        impl_user
        iface_device
        impl_device
        proto_lib
        rust_display
        gRPC::grpc++_reflection
        gRPC::grpc++
        protobuf::libprotobuf
)

add_dependencies(iot_service rust_display)

target_compile_options(iot_service PRIVATE -Wall -Wextra -Wpedantic)
