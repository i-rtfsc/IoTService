#!/bin/bash
set -e

HOOKS_SRC="$(dirname "$0")/git-hooks"
HOOKS_DST="$(git rev-parse --show-toplevel)/.git/hooks"

echo "🔧 正在安装 Git Hooks 到: $HOOKS_DST"

HOOK_FILES=("commit-msg" "prepare-commit-msg" "commit_prompt.py")

for hook in "${HOOK_FILES[@]}"; do
  cp "$HOOKS_SRC/$hook" "$HOOKS_DST/$hook"
  chmod +x "$HOOKS_DST/$hook"
done

echo "✅ Git Hooks 安装完成！请使用 git commit -as 提交代码"
