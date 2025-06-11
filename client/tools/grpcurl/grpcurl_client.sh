#!/bin/bash

# ======================
# gRPC 调试脚本 for IoTService
# ======================

# 配置参数
GRPC_HOST="localhost:50051"
PROTOSET="descriptor.protoset"
SERVICE="iot.IoTService"

# 通用请求字段
DEVICE_ID="device-001"
USER_ID="user-123"
AUTH_TOKEN="token-abc"
TIMESTAMP=$(date +%s%3N) # 当前时间戳（毫秒）

# 检查 grpcurl 是否存在
if ! command -v grpcurl &> /dev/null; then
  echo "❌ 未检测到 grpcurl，请先安装该工具"
  exit 1
fi

# 检查 protoset 文件是否存在
if [ ! -f "$PROTOSET" ]; then
  echo "❌ 未找到描述文件 $PROTOSET"
  exit 1
fi

# 函数：获取当前时间戳（毫秒）
get_millis() {
  echo "$(($(date +%s)*1000 + $(date +%N | cut -c1-3)))"
}

# 获取时间戳
TIMESTAMP=$(get_millis)

# 函数：调用 sendCommand
send_command() {
  echo "📤 调用 sendCommand 接口"
  grpcurl -plaintext \
    -d "{
      \"device_id\": \"$DEVICE_ID\",
      \"command\": \"reboot\",
      \"params\": {
        \"delay\": \"10\"
      },
      \"user_id\": \"$USER_ID\",
      \"auth_token\": \"$AUTH_TOKEN\",
      \"timestamp\": $TIMESTAMP
    }" \
    -protoset "$PROTOSET" \
    "$GRPC_HOST" "$SERVICE/sendCommand"
}

# 函数：调用 reportStatus
report_status() {
  echo "📥 调用 reportStatus 接口"
  grpcurl -plaintext \
    -d "{
      \"device_id\": \"$DEVICE_ID\",
      \"status\": \"online\",
      \"details\": {
        \"battery\": \"90%\",
        \"temperature\": \"36C\"
      },
      \"user_id\": \"$USER_ID\",
      \"auth_token\": \"$AUTH_TOKEN\",
      \"timestamp\": $TIMESTAMP
    }" \
    -protoset "$PROTOSET" \
    "$GRPC_HOST" "$SERVICE/reportStatus"
}

# 函数：列出服务
list_services() {
  echo "📚 列出所有服务"
  grpcurl -plaintext -protoset "$PROTOSET" "$GRPC_HOST" list
}

# 函数：描述服务
describe_service() {
  echo "📝 描述服务 $SERVICE"
  grpcurl -plaintext -protoset "$PROTOSET" "$GRPC_HOST" describe "$SERVICE"
}

# 函数：模拟心跳流
heartbeat() {
  echo "❤️ 模拟双向心跳流 (双向 stream)"
  grpcurl -plaintext \
    -protoset "$PROTOSET" \
    -d @ "$GRPC_HOST" "$SERVICE/heartbeat" <<EOF
    {
      "device_id": "$DEVICE_ID",
      "user_id": "$USER_ID",
      "auth_token": "$AUTH_TOKEN",
      "timestamp": $TIMESTAMP
    }
EOF
}

# ======================
# 主流程：选择调用接口
# ======================

case "$1" in
  send)
    send_command
    ;;
  report)
    report_status
    ;;
  list)
    list_services
    ;;
  describe)
    describe_service
    ;;
  heartbeat)
    heartbeat
    ;;
  *)
    echo "用法: $0 [send|report|list|describe|heartbeat]"
    ;;
esac
