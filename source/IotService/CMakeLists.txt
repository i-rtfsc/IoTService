#cmake_minimum_required(VERSION 3.16)
#project(IotServer)
#
## rust display library
#add_subdirectory(display)
#
#add_executable(IotService
#        main.cpp
#        grpc/iot_service_impl.cpp
#)
#
#target_include_directories(IotService
#        PUBLIC
#        ${PROJECT_SOURCE_DIR}/source/include
#        ${CMAKE_CURRENT_SOURCE_DIR}/include
#)
#
#target_link_libraries(IotService PRIVATE
#        IotUtils
#        IotFramework
#        proto_lib
#        gRPC::grpc++
#        protobuf::libprotobuf
#        display
#)
#
## 关键一步：声明依赖关系，避免 ninja 报错
##add_dependencies(IotService display)
#
#target_compile_options(IotService PRIVATE -Wall -Wextra -Wpedantic)

cmake_minimum_required(VERSION 3.16)
project(IotServer)

# 在顶层定义，供子目录使用
set(RUST_CRATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/display)
set(RUST_TARGET_DIR ${RUST_CRATE_DIR}/target)
set(RUST_LIB_NAME display)

# 打印调试
#message(STATUS "RUST_TARGET_DIR = ${RUST_TARGET_DIR}")
#message(STATUS "RUST_LIB_NAME = ${RUST_LIB_NAME}")

add_subdirectory(display)

# 后续定义
add_executable(IotService
        main.cpp
        grpc/iot_service_impl.cpp
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
        gRPC::grpc++
        protobuf::libprotobuf
        display
)

add_dependencies(IotService display)

target_compile_options(IotService PRIVATE -Wall -Wextra -Wpedantic)
