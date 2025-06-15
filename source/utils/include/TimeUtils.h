#pragma once

#include "common/NameSpaceDef.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

IOT_UTILS_NS_BEGIN

/**
 * @class Time
 * @brief 时间工具类，提供时间格式化、解析、计时等常用功能。
 * @note 支持本地时间与UTC时间的转换，封装 chrono 与 ctime 标准库接口。
 *
 * A utility class for working with time-related operations, including formatting,
 * parsing, and timing measurements using both system and steady clocks.
 */
class Time {
public:
    using Clock = std::chrono::system_clock;
    using SteadyClock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

private:
    /**
     * @brief 将 time_t 转换为本地时间结构体（线程安全）
     *        Convert `time_t` to local time in a thread-safe manner.
     * @param time 输入的 time_t 时间戳
     * @return 本地时间的 tm 结构体
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::tm toLocalTime(std::time_t time) {
        std::tm result {};
#ifdef _WIN32
        if (localtime_s(&result, &time) != 0) {
            throw std::runtime_error("Failed to convert to local time (localtime_s)");
        }
#else
        if (!localtime_r(&time, &result)) {
            throw std::runtime_error("Failed to convert to local time (localtime_r)");
        }
#endif
        return result;
    }

    /**
     * @brief 将 time_t 转换为 UTC 时间结构体（线程安全）
     *        Convert `time_t` to UTC time in a thread-safe manner.
     * @param time 输入的 time_t 时间戳
     * @return UTC 时间的 tm 结构体
     * @throws std::runtime_error 转换失败时抛出异常
     */
    static std::tm toUtcTime(std::time_t time) {
        std::tm result {};
#ifdef _WIN32
        if (gmtime_s(&result, &time) != 0) {
            throw std::runtime_error("Failed to convert to UTC time (gmtime_s)");
        }
#else
        if (!gmtime_r(&time, &result)) {
            throw std::runtime_error("Failed to convert to UTC time (gmtime_r)");
        }
#endif
        return result;
    }

    /**
     * @brief 格式化时间为字符串（支持毫秒，默认本地时间）
     *        Format a chrono::time_point to string with optional millisecond suffix.
     * @tparam ClockType 时钟类型（system_clock 或 steady_clock）
     * @param tp 时间点
     * @param fmt 格式化字符串（strftime格式）
     * @param forFilename 是否用于文件名（影响分隔符）
     * @return 格式化后的时间字符串
     */
    template <typename ClockType>
    static std::string format(const typename ClockType::time_point& tp, const std::string& fmt, bool forFilename = false) {
        using namespace std::chrono;
        auto ms = duration_cast<milliseconds>(tp.time_since_epoch()) % 1000;
        std::time_t t = ClockType::to_time_t(tp);
        std::tm tm = toLocalTime(t);

        std::ostringstream oss;
        oss << std::put_time(&tm, fmt.c_str());
        oss << (forFilename ? "." : ".") << std::setw(3) << std::setfill('0') << ms.count();
        return oss.str();
    }

public:
    /**
     * @brief 获取当前时间字符串，格式为 "YYYY-MM-DD HH:MM:SS.mmm"
     *        Get current local time string with milliseconds.
     */
    static std::string formatNow() {
        return format<Clock>(Clock::now(), "%Y-%m-%d %H:%M:%S");
    }

    /**
     * @brief 获取当前时间字符串用于文件名，格式为 "YYYY.MM.DD-HH.MM.SS.mmm"
     *        Get current time string formatted for filenames.
     */
    static std::string formatNowForFilename() {
        return format<Clock>(Clock::now(), "%Y.%m.%d-%H.%M.%S", true);
    }

    /**
     * @brief 获取当前 UTC 时间字符串，格式为 "YYYY-MM-DD HH:MM:SS.mmm UTC"
     *        Get current UTC time string with milliseconds and UTC suffix.
     */
    static std::string formatNowUtc() {
        using namespace std::chrono;
        auto now = Clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        std::time_t t = Clock::to_time_t(now);
        std::tm tm = toUtcTime(t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
            << "." << std::setw(3) << std::setfill('0') << ms.count()
            << " UTC";
        return oss.str();
    }

    /**
     * @brief 获取当前时间戳（单位：秒）
     *        Get current system time as a Unix timestamp in seconds.
     */
    static int64_t timestampSec() {
        return static_cast<int64_t>(Clock::to_time_t(Clock::now()));
    }

    /**
     * @brief 获取当前时间戳（单位：毫秒）
     *        Get current system time as a Unix timestamp in milliseconds.
     */
    static int64_t timestampMs() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   Clock::now().time_since_epoch())
            .count();
    }

    /**
     * @brief 获取 SteadyClock 运行时间差（用于性能测量）
     *        Measure elapsed time since a start point using SteadyClock.
     * @tparam Duration 返回的时间单位，默认毫秒
     * @param start 起始时间点
     * @return 与当前时间的时间差
     */
    template <typename Duration = std::chrono::milliseconds>
    static Duration elapsedSince(const SteadyClock::time_point& start) {
        return std::chrono::duration_cast<Duration>(SteadyClock::now() - start);
    }

    /**
     * @brief 将时间戳（秒）转换为可读字符串
     *        Convert a timestamp (in seconds) to readable string.
     * @param timestampSec 秒级时间戳
     * @return 时间字符串 "YYYY-MM-DD HH:MM:SS"
     */
    static std::string timestampToString(int64_t timestampSec) {
        std::tm tm = toLocalTime(static_cast<std::time_t>(timestampSec));
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    /**
     * @brief 将时间字符串解析为时间戳（秒）
     *        Parse datetime string to Unix timestamp in seconds.
     * @param datetime 时间字符串，格式要求 "YYYY-MM-DD HH:MM:SS"
     * @return 秒级时间戳
     * @throws std::invalid_argument 格式不匹配时抛出异常
     */
    static int64_t parseTimeString(const std::string& datetime) {
        std::tm tm = {};
        std::istringstream iss(datetime);
        iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (iss.fail()) {
            throw std::invalid_argument("Invalid datetime format. Expected: YYYY-MM-DD HH:MM:SS");
        }
        return static_cast<int64_t>(std::mktime(&tm));
    }
};

IOT_UTILS_NS_END
