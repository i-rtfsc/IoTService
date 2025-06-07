#pragma once

#include "NameSpaceDef.h"
#include <functional>
#include <mutex>
#include <optional>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

IOT_COMMON_NS_BEGIN

template <typename Key, typename Value, size_t SHARD_COUNT = 16>
class ShardedMap {
public:
    ShardedMap() : mShards(SHARD_COUNT) {}

    void insert(const Key& key, const Value& value) {
        auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        shard.mMap[key] = value;
    }

    std::optional<Value> get(const Key& key) const {
        const auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        auto it = shard.mMap.find(key);
        if (it != shard.mMap.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    bool erase(const Key& key) {
        auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        return shard.mMap.erase(key) > 0;
    }

    bool contains(const Key& key) const {
        const auto& shard = getShard(key);
        std::lock_guard<std::mutex> lock(shard.mMutex);
        return shard.mMap.find(key) != shard.mMap.end();
    }

    void clear() {
        for (auto& shard : mShards) {
            std::lock_guard<std::mutex> lock(shard.mMutex);
            shard.mMap.clear();
        }
    }

private:
    struct Shard {
        mutable std::mutex mMutex;
        std::unordered_map<Key, Value> mMap;
    };

    std::vector<Shard> mShards;

    Shard& getShard(const Key& key) {
        size_t hash = std::hash<Key> {}(key);
        return mShards[hash % SHARD_COUNT];
    }

    const Shard& getShard(const Key& key) const {
        size_t hash = std::hash<Key> {}(key);
        return mShards[hash % SHARD_COUNT];
    }
};

IOT_COMMON_NS_END
