import os
import re
import optparse

COMMENT_PATTERNS = {
    # 单行注释, 多行注释
    '.c':      (r'//.*', r'/\*[\s\S]*?\*/'),
    '.cpp':    (r'//.*', r'/\*[\s\S]*?\*/'),
    '.cc':     (r'//.*', r'/\*[\s\S]*?\*/'),
    '.h':      (r'//.*', r'/\*[\s\S]*?\*/'),
    '.hpp':    (r'//.*', r'/\*[\s\S]*?\*/'),
    '.java':   (r'//.*', r'/\*[\s\S]*?\*/'),
    '.js':     (r'//.*', r'/\*[\s\S]*?\*/'),
    '.ts':     (r'//.*', r'/\*[\s\S]*?\*/'),
    '.rs':     (r'//.*', r'/\*[\s\S]*?\*/'),
    '.py':     (r'#.*', r'(\'\'\'[\s\S]*?\'\'\'|\"\"\"[\s\S]*?\"\"\")'),
    '.sh':     (r'#.*', None),
    '.bash':   (r'#.*', None),
    '.cmake':  (r'#.*', None),
    '.html':   (r'<!--[\s\S]*?-->', None),
    '.xml':    (r'<!--[\s\S]*?-->', None),
    '.yaml':   (r'#.*', None),
    '.yml':    (r'#.*', None),
    '.toml':   (r'#.*', None),
}

def remove_comments(code: str, ext: str) -> str:
    ext = ext.lower()
    patterns = COMMENT_PATTERNS.get(ext)
    if not patterns:
        return code  # 不支持的语言，原样返回

    line_comment, block_comment = patterns
    if block_comment:
        code = re.sub(block_comment, '', code, flags=re.MULTILINE)
    if line_comment:
        code = re.sub(line_comment, '', code)
    return code

def tree_view(path, prefix=''):
    tree_lines = []
    entries = sorted(os.listdir(path))
    files = [e for e in entries if os.path.isfile(os.path.join(path, e))]
    dirs = [e for e in entries if os.path.isdir(os.path.join(path, e))]
    entries = dirs + files
    for idx, entry in enumerate(entries):
        full_path = os.path.join(path, entry)
        connector = '└── ' if idx == len(entries) - 1 else '├── '
        tree_lines.append(f"{prefix}{connector}{entry}")
        if os.path.isdir(full_path):
            extension = '    ' if idx == len(entries) - 1 else '│   '
            tree_lines.extend(tree_view(full_path, prefix + extension))
    return tree_lines

def dump_file_contents(base_path, output_lines, keep_comments=False):
    for root, _, files in os.walk(base_path):
        for file in sorted(files):
            file_path = os.path.join(root, file)
            ext = os.path.splitext(file)[1]
            relative_path = os.path.relpath(file_path, start=os.getcwd())
            output_lines.append(f"\n📄 {relative_path} 文件的内容如下：\n")
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                    if not keep_comments:
                        content = remove_comments(content, ext)
            except Exception as e:
                content = f"❌ 无法读取文件内容: {e}"
            output_lines.append(content.strip())
            output_lines.append("\n" + "-" * 80 + "\n")

def parse_args():
    parser = optparse.OptionParser()
    parser.add_option('-p', '--path', dest='path', help='要扫描的路径')
    parser.add_option('--keep-comments', action='store_true', dest='keep_comments', default=False, help='是否保留注释')
    parser.add_option('-o', '--output', dest='output', default='output.txt', help='输出文件名（默认：output.txt）')
    return parser.parse_args()

def main():
    (options, _) = parse_args()
    if not options.path:
        print("❌ 必须指定 --path 参数")
        return

    base_path = os.path.abspath(options.path)
    if not os.path.exists(base_path):
        print(f"❌ 路径不存在: {base_path}")
        return

    output_lines = []
    output_lines.append(f"📁 目录结构：{options.path}\n")
    output_lines.extend(tree_view(base_path))

    dump_file_contents(base_path, output_lines, keep_comments=options.keep_comments)

    with open(options.output, 'w', encoding='utf-8') as f:
        f.write('\n'.join(output_lines))

    print(f"✅ 输出已写入 {options.output}")

if __name__ == "__main__":
    main()
