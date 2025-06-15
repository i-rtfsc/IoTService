#include "TimeUtils.h"
#include "common/NameSpaceDef.h"

#include <gtest/gtest.h>
#include <iostream>
#include <thread>

using IOT_UTILS_NS::Time;

TEST(TimeTest, FormatNowNotEmpty) {
    std::string now = Time::formatNow();
    std::cout << "[FormatNowNotEmpty] now = " << now << std::endl;
    EXPECT_FALSE(now.empty());
    EXPECT_EQ(now.length(), 23); // 格式：2025-06-14 12:34:56.123
}

TEST(TimeTest, FormatNowForFilename) {
    std::string now = Time::formatNowForFilename();
    std::cout << "[FormatNowForFilename] now = " << now << std::endl;
    EXPECT_FALSE(now.empty());
    EXPECT_EQ(now.length(), 23); // 格式：2025.06.14-12.34.56.123
}

TEST(TimeTest, FormatNowUtcContainsUTC) {
    std::string utc = Time::formatNowUtc();
    std::cout << "[FormatNowUtcContainsUTC] utc = " << utc << std::endl;
    EXPECT_NE(utc.find("UTC"), std::string::npos);
}

TEST(TimeTest, TimestampConversion) {
    int64_t ts = Time::timestampSec();
    std::string str = Time::timestampToString(ts);
    int64_t ts2 = Time::parseTimeString(str);

    std::cout << "[TimestampConversion] ts = " << ts
              << ", str = " << str << ", ts2 = " << ts2 << std::endl;

    EXPECT_NEAR(ts, ts2, 1); // 可能有±1秒误差
}

TEST(TimeTest, DurationSinceWorks) {
    auto start = Time::SteadyClock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto dur = Time::elapsedSince(start);
    std::cout << "[DurationSinceWorks] duration = " << dur.count() << " ms" << std::endl;
    EXPECT_GE(dur.count(), 10);
}

TEST(TimeTest, InvalidParseThrows) {
    try {
        Time::parseTimeString("invalid format");
        FAIL() << "[InvalidParseThrows] Expected exception not thrown.";
    } catch (const std::invalid_argument& e) {
        std::cout << "[InvalidParseThrows] Caught exception: " << e.what() << std::endl;
        SUCCEED();
    } catch (...) {
        FAIL() << "[InvalidParseThrows] Unexpected exception type.";
    }
}
