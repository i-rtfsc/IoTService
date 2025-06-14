#pragma once

#include "NameSpaceDef.h"
#include <functional>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

IOT_NS_BEGIN

constexpr size_t kDEFAULT_SHARD_COUNT = 16;

/**
 * @brief 分片哈希映射类，用于实现高效的线程安全键值存储
 *
 * This is a sharded hash map implementation for efficient thread-safe
 * key-value storage. By dividing the map into multiple shards, it
 * reduces lock contention under concurrent access.
 *
 * @tparam Key     键类型 Key type
 * @tparam Value   值类型 Value type
 * @tparam SHARD_COUNT  分片数，默认16 Number of shards, default is 16
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-07
 */
template <typename Key, typename Value, size_t SHARD_COUNT = kDEFAULT_SHARD_COUNT>
class ShardedMap {
public:
    /**
     * @brief 构造函数，初始化 SHARD_COUNT 个分片
     *
     * Constructor initializes the vector with SHARD_COUNT shards.
     */
    ShardedMap()
        : mShards(SHARD_COUNT) {}

    /**
     * @brief 插入或更新键值对
     *
     * Insert or update a key-value pair in the map.
     * 线程安全，会对目标分片加锁。
     * Thread-safe, locks the shard corresponding to the key.
     *
     * @param key   要插入的键 Key to insert
     * @param value 要插入的值 Value to insert
     */
    void insert(const Key& key, const Value& value) {
        auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        shard.mMap[key] = value;
    }

    /**
     * @brief 查询键对应的值
     *
     * Find the value associated with the given key.
     * 线程安全，对目标分片加锁。
     * Thread-safe, locks the shard for reading.
     *
     * @param key 需要查询的键 Key to query
     * @return std::optional<Value> 返回对应的值，如果不存在则返回 std::nullopt
     * Optional containing value if found, nullopt otherwise.
     */
    [[nodiscard]]
    auto get(const Key& key) const -> std::optional<Value> {
        const auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        auto it = shard.mMap.find(key);
        if (it != shard.mMap.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    /**
     * @brief 删除指定键的元素
     *
     * Remove the element with the given key.
     * 线程安全，对目标分片加锁。
     * Thread-safe, locks the shard.
     *
     * @param key 要删除的键 Key to remove
     * @return true 删除成功，false 如果键不存在
     * True if an element was removed, false if not found.
     */
    auto erase(const Key& key) -> bool {
        auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        return shard.mMap.erase(key) > 0;
    }

    /**
     * @brief 判断是否包含指定键
     *
     * Check if the key exists in the map.
     * 线程安全，对目标分片加锁。
     * Thread-safe, locks the shard.
     *
     * @param key 要检测的键 Key to check
     * @return true 存在，false 不存在
     * True if key exists, false otherwise.
     */
    [[nodiscard]]
    auto contains(const Key& key) const -> bool {
        const auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        return shard.mMap.find(key) != shard.mMap.end();
    }

    /**
     * @brief 清空所有键值对
     *
     * Clear all elements in all shards.
     * 线程安全，会依次对所有分片加锁。
     * Thread-safe, locks all shards in turn.
     */
    void clear() {
        for (auto& shard : mShards) {
            std::lock_guard<std::mutex> lock(shard.mMutex);
            shard.mMap.clear();
        }
    }

private:
    /**
     * @brief 单个分片，包含一个互斥锁和一个unordered_map
     *
     * Single shard contains its own mutex and map.
     */
    struct Shard {
        mutable std::mutex mMutex;           // 保护本分片的互斥锁 Mutex protecting this shard
        std::unordered_map<Key, Value> mMap; // 本分片的键值存储 Key-value map of this shard
    };

    std::vector<Shard> mShards; // 所有分片的集合 Vector holding all shards

    /**
     * @brief 根据 key 计算分片索引（非 const 版本）
     *
     * Compute the shard index for the given key (non-const).
     *
     * @param key 输入键 Key
     * @return Shard& 返回对应分片的引用 Reference to the shard
     */
    auto getShard(const Key& key) -> Shard& {
        size_t hash = std::hash<Key> {}(key);
        return mShards[hash % SHARD_COUNT];
    }

    /**
     * @brief 根据 key 计算分片索引（const 版本）
     *
     * Compute the shard index for the given key (const).
     *
     * @param key 输入键 Key
     * @return const Shard& 返回对应分片的常量引用 Const reference to the shard
     */
    [[nodiscard]]
    auto getShard(const Key& key) const -> const Shard& {
        size_t hash = std::hash<Key> {}(key);
        return mShards[hash % SHARD_COUNT];
    }
};

IOT_NS_END
