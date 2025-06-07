#pragma once

#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#ifdef __ANDROID__
#include <android/log.h>

namespace detail {

// Android 平台，用指定 kTAG 打印日志
inline void logPrint(int level, const char* kTAG, const char* fmt, va_list args) {
    __android_log_vprint(level, kTAG, fmt, args);
}

inline void logPrintWrapper(int level, const char* kTAG, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    logPrint(level, kTAG, fmt, args);
    va_end(args);
}

} // namespace detail

#define LOGI(kTAG, fmt, ...) detail::logPrintWrapper(ANDROID_LOG_INFO, kTAG, fmt, ##__VA_ARGS__)
#define LOGD(kTAG, fmt, ...) detail::logPrintWrapper(ANDROID_LOG_DEBUG, kTAG, fmt, ##__VA_ARGS__)
#define LOGW(kTAG, fmt, ...) detail::logPrintWrapper(ANDROID_LOG_WARN, kTAG, fmt, ##__VA_ARGS__)
#define LOGE(kTAG, fmt, ...) detail::logPrintWrapper(ANDROID_LOG_ERROR, kTAG, fmt, ##__VA_ARGS__)
#define LOGV(kTAG, fmt, ...) detail::logPrintWrapper(ANDROID_LOG_VERBOSE, kTAG, fmt, ##__VA_ARGS__)

#else // 非 Android 平台

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_RESET "\033[0m"

inline std::string getCurrentTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t t = system_clock::to_time_t(now);
    std::tm tm {};
    localtime_r(&t, &tm);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << (tm.tm_mon + 1) << "-" << std::setw(2) << tm.tm_mday << " "
        << std::setw(2) << tm.tm_hour << ":" << std::setw(2) << tm.tm_min << ":" << std::setw(2) << tm.tm_sec << "."
        << std::setw(3) << ms.count();
    return oss.str();
}

inline void logFormat(const char* levelColor, const char* levelStr, const char* kTAG, const char* fmt, va_list args) {
    std::string timestamp = getCurrentTimestamp();
    printf("%s %s%s%s %-12s: ", timestamp.c_str(), levelColor, levelStr, COLOR_RESET, kTAG);
    vprintf(fmt, args);
    printf("\n");
}

namespace detail {

inline void logPrintWrapper(const char* levelColor, const char* levelStr, const char* kTAG, const char* fmt,
                            va_list args) {
    logFormat(levelColor, levelStr, kTAG, fmt, args);
}

inline void logPrintWrapper(const char* levelColor, const char* levelStr, const char* kTAG, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    logPrintWrapper(levelColor, levelStr, kTAG, fmt, args);
    va_end(args);
}

} // namespace detail

#define LOGI(kTAG, fmt, ...) detail::logPrintWrapper(COLOR_GREEN, "I", kTAG, fmt, ##__VA_ARGS__)
#define LOGD(kTAG, fmt, ...) detail::logPrintWrapper(COLOR_BLUE, "D", kTAG, fmt, ##__VA_ARGS__)
#define LOGW(kTAG, fmt, ...) detail::logPrintWrapper(COLOR_YELLOW, "W", kTAG, fmt, ##__VA_ARGS__)
#define LOGE(kTAG, fmt, ...) detail::logPrintWrapper(COLOR_RED, "E", kTAG, fmt, ##__VA_ARGS__)
#define LOGV(kTAG, fmt, ...) detail::logPrintWrapper(COLOR_CYAN, "V", kTAG, fmt, ##__VA_ARGS__)

#endif
