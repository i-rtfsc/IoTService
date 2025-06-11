# 在顶层定义，供子目录使用
set(RUST_CRATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/display)
set(RUST_TARGET_DIR ${RUST_CRATE_DIR}/target)
set(RUST_LIB_NAME display)

add_subdirectory(display)

# 后续定义
add_executable(IotService
        main.cpp
        grpc/IoTServiceImpl.cpp
)

target_include_directories(IotService
        PUBLIC
        ${PROJECT_SOURCE_DIR}/source/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(IotService PRIVATE
        IotUtils
        IotFramework
        proto_lib
        display
        gRPC::grpc++_reflection
        gRPC::grpc++
        protobuf::libprotobuf
)

add_dependencies(IotService display)

target_compile_options(IotService PRIVATE -Wall -Wextra -Wpedantic)
