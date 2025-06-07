brew uninstall grpc protobuf protobuf@21 protobuf@29 protobuf@3
sudo rm -rf /usr/local/include/google
sudo rm -rf /usr/local/include/grpc*
sudo rm -rf /usr/local/lib/libprotobuf*
sudo rm -rf /usr/local/lib/libprotoc*
sudo rm -rf /usr/local/lib/libgrpc*
sudo rm -rf /usr/local/lib/cmake/protobuf
sudo rm -rf /usr/local/lib/cmake/grpc
sudo rm -f /usr/local/lib/pkgconfig/protobuf*
sudo rm -f /usr/local/lib/pkgconfig/grpc*


#brew install protobuf@21
#brew link --force --overwrite protobuf@21
#
#brew install grpc
#
#protoc --version
## libprotoc 3.21.x
#
#grpc_cpp_plugin --version
## 应该不会报错
