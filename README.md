## 依赖

### 安装 `gRPC`

```bash
git clone --recurse-submodules -b v1.72.0 https://github.com/grpc/grpc
cd grpc
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make -j2
# 直接 sudo make install 会报错，原因是：有些子任务没有继承sudo权限
#sudo make install

# 将文件“安装”到一个中转目录
make install DESTDIR=/tmp/grpc-install
sudo cp -R /tmp/grpc-install/usr/local/* /usr/local/
```

到这里之后，`gRPC`自带的 `protoc` 版本过低，导致运行工程会报错，需要下载 21.x 的`protoc`。

### 安装 `protobuf`

`Macos` 下载 `protobuf` 21.x 源码编译报错，改成 `brew` 安装。

```bash
brew install protobuf@21
```

配置环境变量

```bash

# 设置 protobuf@21 的路径
export PATH="/usr/local/opt/protobuf@21/bin:$PATH"
export LDFLAGS="-L/usr/local/opt/protobuf@21/lib"
export CPPFLAGS="-I/usr/local/opt/protobuf@21/include"
export PKG_CONFIG_PATH="/usr/local/opt/protobuf@21/lib/pkgconfig"

```

cmake配置

```bash

set(Protobuf_INCLUDE_DIR "/usr/local/opt/protobuf@21/include")
set(Protobuf_LIBRARY "/usr/local/opt/protobuf@21/lib/libprotobuf.dylib")
set(Protobuf_PROTOC_EXECUTABLE "/usr/local/opt/protobuf@21/bin/protoc")

find_package(Protobuf REQUIRED)
set(Protobuf_LIBRARIES "/usr/local/opt/protobuf@21/lib/libprotobuf.dylib")

```

### python

```bash
pip install grpcio grpcio-tools
```

