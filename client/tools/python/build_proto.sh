#!/bin/bash

rm -rf *pb2*
rm -rf __pycache__

PROTO_DIR=../../../proto
OUT_DIR=.

python -m grpc_tools.protoc \
  -I${PROTO_DIR} \
  --python_out=${OUT_DIR} \
  --grpc_python_out=${OUT_DIR} \
  ${PROTO_DIR}/iot_service.proto

