#pragma once

// 定义命名空间前缀
#define IOT_NS com::rtfsc::iot

// 一级命名空间
#define IOT_NS_BEGIN namespace IOT_NS {
#define IOT_NS_END }

// common 模块
#define IOT_COMMON_NS IOT_NS::common
#define IOT_COMMON_NS_BEGIN namespace IOT_COMMON_NS {
#define IOT_COMMON_NS_END }

// framework 模块
#define IOT_FRAMEWORK_NS IOT_NS::framework
#define IOT_FRAMEWORK_NS_BEGIN namespace IOT_FRAMEWORK_NS {
#define IOT_FRAMEWORK_NS_END }

// utils 模块
#define IOT_UTILS_NS IOT_NS::utils
#define IOT_UTILS_NS_BEGIN namespace IOT_UTILS_NS {
#define IOT_UTILS_NS_END }

// server 模块
#define IOT_SERVER_NS IOT_NS::server
#define IOT_SERVER_NS_BEGIN namespace IOT_SERVER_NS {
#define IOT_SERVER_NS_END }
