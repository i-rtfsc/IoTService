#!/bin/bash
# 检查所有 .cpp 和 .h 文件是否符合 clang-format 规范，支持排除多个目录

FAILED=0

# 要排除的目录列表
EXCLUDE_DIRS=(
  "./build"
  "./cmake-build-debug"
  "./out"
)

# 构造 find 命令参数
FIND_CMD=(find . \( -name "*.cpp" -o -name "*.h" \))

# 添加排除路径
for dir in "${EXCLUDE_DIRS[@]}"; do
    FIND_CMD+=(! -path "$dir/*")
done

# 执行 find 命令并遍历文件
FILES=$("${FIND_CMD[@]}")

for file in $FILES; do
    clang-format --dry-run --Werror "$file"
    if [[ $? -ne 0 ]]; then
        echo "[FAILED] $file"
        FAILED=1
    fi
done

if [[ $FAILED -ne 0 ]]; then
    echo "Some files are not properly formatted. Please run: make format"
    exit 1
else
    echo "All source files are properly formatted."
fi
