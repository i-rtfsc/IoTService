# Clang-Tidy 全工程静态检查使用说明

本工程使用 `clang-tidy` 进行 C++ 代码静态检查，支持在构建过程中检查单文件，也支持一次性检查整个工程的所有文件。

## 前置条件

请确保你已经完成以下准备：

- 工程为标准 CMake 工程
- `compile_commands.json` 已在 `cmake-build-debug/` 目录生成
- 已安装 `clang-tidy` 与 `run-clang-tidy` 工具

## 生成 compile_commands.json

确保 CMakeLists.txt 中已设置：

```cmake

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

```

或者在配置时添加该选项：

```bash

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B cmake-build-debug

```

## 安装 clang-tidy 工具

- Ubuntu / Debian

```bash

sudo apt install clang-tidy clang-tools

```

- macOS

```bash

brew install llvm

```

安装后可通过以下方式确认：

```bash

clang-tidy --version
run-clang-tidy --version

```

## 一键检查整个项目

你可以使用以下脚本完成一次性全工程检查：

```bash

bash scripts/run-clang-tidy.sh

```

> 同时会检查 `cmake-build-debug/` 目录下的所有源文件。

只检查某个目录或文件：

```bash

bash scripts/run-clang-tidy.sh source

```