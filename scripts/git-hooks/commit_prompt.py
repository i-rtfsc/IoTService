#!/usr/bin/env python3
import sys

types = [
    ('feat', '✨ 新功能'),
    ('fix', '🐞 修复问题'),
    ('refactor', '🧹 代码重构'),
    ('perf', '⚡ 性能优化'),
    ('docs', '📝 文档更新'),
    ('style', '🎨 代码样式调整'),
    ('test', '🧪 添加或修改测试'),
    ('chore', '🧹 构建/辅助工具变更'),
    ('ci', '🔁 CI 配置修改'),
    ('build', '🛠️ 构建系统调整'),
    ('deps', '📦 依赖变更'),
    ('infra', '🧱 基础设施变更'),
    ('security', '🔐 安全性修复'),
    ('revert', '⏪ 回退提交'),
    ('breaking', '💥 破坏性修改'),
]

scopes = ['api', 'codec', 'sync', 'cli', 'tools', 'grpc', 'network', 'render', 'auth', 'system', 'user', 'ffmpeg']

def choose(prompt, options):
    print(prompt)
    for i, (k, label) in enumerate(options, 1):
        print(f"{i}. {k:<10} {label}")
    idx = input("请选择编号: ").strip()
    if idx.isdigit() and 1 <= int(idx) <= len(options):
        return options[int(idx) - 1][0]
    else:
        print("❌ 输入无效")
        sys.exit(1)

def choose_scope():
    print("选择作用域（留空为无，输入编号或自定义）:")
    for i, s in enumerate(scopes, 1):
        print(f"{i}. {s}")
    val = input("Scope: ").strip()
    if val == "":
        return ""
    elif val.isdigit() and 1 <= int(val) <= len(scopes):
        return scopes[int(val) - 1]
    return val

def main():
    commit_file = sys.argv[1]
    type_ = choose("请选择提交类型:", types)
    scope = choose_scope()
    subject = input("请输入简要描述: ").strip()
    if not subject:
        print("❌ 描述不能为空")
        sys.exit(1)
    full_msg = f"{type_}({scope}): {subject}" if scope else f"{type_}: {subject}"
    with open(commit_file, "w") as f:
        f.write(full_msg + "\n")

if __name__ == "__main__":
    main()

