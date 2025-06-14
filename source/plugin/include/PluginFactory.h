#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @brief 通用插件工厂模板类
 *        Generic plugin factory for registering and creating named instances.
 *
 * @tparam Base 插件基类类型 / Base class type of the plugin
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-12
 */
template <typename Base>
class PluginFactory {
public:
    // 创建器类型定义：返回共享指针的函数对象
    // Type alias for a creator function returning a shared pointer to Base
    using Creator = std::function<std::shared_ptr<Base>()>;

    // 禁止拷贝构造和赋值操作，确保单例唯一性
    // Disable copy and assignment to enforce singleton pattern
    PluginFactory(const PluginFactory&) = delete;
    PluginFactory& operator=(const PluginFactory&) = delete;

    /**
     * @brief 获取插件工厂单例实例
     *        Get singleton instance of the plugin factory
     *
     * @return PluginFactory& 工厂实例引用 / Reference to the singleton factory
     */
    static PluginFactory& instance() {
        static PluginFactory factory;
        return factory;
    }

    /**
     * @brief 注册插件创建器
     *        Register a creator function for the specified type name
     *
     * @param typeName 插件类型名称 / Plugin type name
     * @param creator 创建器函数对象 / Creator function object
     * @throws std::invalid_argument 若 creator 为空 / Throws if creator is null
     */
    void registerCreator(const std::string& typeName, Creator creator) {
        std::scoped_lock lock(mMutex);
        if (!creator) {
            throw std::invalid_argument("Creator cannot be null for type: " + typeName);
        }
        mCreators[typeName] = std::move(creator);
    }

    /**
     * @brief 创建指定名称的插件实例
     *        Create a plugin instance by its registered type name
     *
     * @param typeName 插件类型名称 / Plugin type name
     * @return std::shared_ptr<Base> 插件实例共享指针（可能为空）/ Shared pointer to the plugin instance (may be null)
     */
    [[nodiscard]]
    std::shared_ptr<Base> create(const std::string& typeName) const {
        std::scoped_lock lock(mMutex);
        auto it = mCreators.find(typeName);
        if (it != mCreators.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    // 构造函数私有化，确保只能通过 instance() 获取对象
    // Private constructor to enforce singleton usage
    PluginFactory() = default;

    // 成员变量：注册的创建器映射表 / Mapping from type name to creator functions
    std::unordered_map<std::string, Creator> mCreators;

    // 成员变量：用于保护并发访问 / Mutex to ensure thread-safe access
    mutable std::mutex mMutex;
};
