#!/bin/bash
# scripts/run-clang-tidy-check.sh
# 运行 clang-tidy 检查整个工程（适配 CLion 的 cmake-build-debug 输出目录）

set -e

# 当前脚本目录
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/cmake-build-debug"

# 检查 compile_commands.json 是否存在
COMPILE_COMMANDS="$BUILD_DIR/compile_commands.json"
if [ ! -f "$COMPILE_COMMANDS" ]; then
  echo "[ERROR] 找不到 $COMPILE_COMMANDS"
  echo "请先使用 CLion 构建一次项目，或手动运行："
  echo "  cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B cmake-build-debug"
  exit 1
fi

# 检查 run-clang-tidy 是否可用
if ! command -v run-clang-tidy &> /dev/null; then
  echo "[ERROR] 未安装 run-clang-tidy 工具，请先安装 clang-tools。"
  echo "例如在 Ubuntu 上使用：sudo apt install clang-tools"
  exit 2
fi

# 支持传入目标路径，默认是 source/
TARGETS=("$@")
if [ ${#TARGETS[@]} -eq 0 ]; then
  TARGETS=("source")
fi

# 提示信息
echo "[INFO] 使用 clang-tidy 检查代码，构建目录为：$BUILD_DIR"
echo "[INFO] 检查目标：${TARGETS[*]}"

# 执行 clang-tidy
run-clang-tidy -p "$BUILD_DIR" "${TARGETS[@]}"
