#!/bin/bash

# 清除旧文件
rm -f descriptor.protoset

# 定义路径
PROTO_DIR=../../../proto
OUT_DIR=.

# 确保 proto 文件存在
if [ ! -f ${PROTO_DIR}/iot_service.proto ]; then
  echo "proto 文件未找到: ${PROTO_DIR}/iot_service.proto"
  exit 1
fi

# 生成 descriptor
protoc \
  --proto_path=${PROTO_DIR} \
  --include_imports \
  --include_source_info \
  --descriptor_set_out=${OUT_DIR}/descriptor.protoset \
  ${PROTO_DIR}/iot_service.proto

# 检查是否生成成功
if [ $? -ne 0 ] || [ ! -s "${OUT_DIR}/descriptor.protoset" ]; then
  echo "descriptor.protoset 生成失败或为空"
  exit 1
fi

echo "descriptor.protoset 生成成功"
