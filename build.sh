#!/bin/bash

set -e  # 有错误立即退出
set -o pipefail

BUILD_DIR="build"
TARGET="iot_server"

echo "正在准备构建目录..."
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

echo "正在运行 CMake 配置..."
cmake ..

echo "开始编译目标：${TARGET} ..."
cmake --build . --target ${TARGET} -j$(nproc)

echo "构建成功！目标文件路径：${BUILD_DIR}/server/unix/${TARGET}"