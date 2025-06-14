#pragma once

// 定义命名空间前缀
#define IOT_NS com::rtfsc::iot

// 一级命名空间
#define IOT_NS_BEGIN namespace IOT_NS {
#define IOT_NS_END }

// user 模块
#define IOT_USER_NS IOT_NS::user
#define IOT_USER_NS_BEGIN namespace IOT_USER_NS {
#define IOT_USER_NS_END }

// device 模块
#define IOT_DEVICE_NS IOT_NS::device
#define IOT_DEVICE_NS_BEGIN namespace IOT_DEVICE_NS {
#define IOT_DEVICE_NS_END }

// task 模块
#define IOT_TASK_NS IOT_NS::task
#define IOT_TASK_NS_BEGIN namespace IOT_TASK_NS {
#define IOT_TASK_NS_END }

// utils 模块
#define IOT_UTILS_NS IOT_NS::utils
#define IOT_UTILS_NS_BEGIN namespace IOT_UTILS_NS {
#define IOT_UTILS_NS_END }

// server 模块
#define IOT_SERVER_NS IOT_NS::server
#define IOT_SERVER_NS_BEGIN namespace IOT_SERVER_NS {
#define IOT_SERVER_NS_END }
