## `gRPC`

### 源码编译安装 `gRPC`


```bash

git clone --recurse-submodules -b v1.73.0 https://github.com/grpc/grpc

cd grpc

mkdir build && cd build

cmake .. \
  -DCMAKE_INSTALL_PREFIX=/usr/local
  
make -j2

# 直接 sudo make install 会报错，原因是：有些子任务没有继承sudo权限
#sudo make install

# 先清理一下之前的安装（如果有的话）
#sudo rm -rf /usr/local/include/grpc /usr/local/lib/libgrpc* /usr/local/bin/grpc_*

# 将文件“安装”到一个中转目录
make install DESTDIR=/tmp/grpc-install
sudo cp -R /tmp/grpc-install/usr/local/* /usr/local/

```

## python grpc

```bash

pip install grpcio grpcio-tools

```
