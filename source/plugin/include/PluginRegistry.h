#pragma once

#include "PluginFactory.h"
#include <memory>
#include <string>
#include <type_traits>

/**
 * @class PluginRegistrar
 * @brief 注册插件到 PluginFactory 的模板工具类。
 *
 * 该类用于在静态初始化阶段注册插件名称与对应的构造函数（creator），
 * 从而支持基于字符串名称的插件动态创建。
 *
 * @tparam Base 插件基类类型，所有注册的插件类型都必须继承自该类。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-15
 */
template <typename Base>
class PluginRegistrar {
public:
    /**
     * @brief 构造函数，用于注册插件类型。
     *
     * @param name 插件名称，用于在 PluginFactory 中唯一标识。
     * @param creator 插件构造函数，返回值为 std::shared_ptr<Base> 类型。
     *
     * 注册时会通过 static_assert 检查返回类型是否继承自 Base，确保类型安全。
     */
    PluginRegistrar(const std::string& name, std::function<std::shared_ptr<Base>()> creator) {
        // 编译期类型检查，确保 creator 返回类型派生自 Base。
        static_assert(std::is_base_of<Base, typename decltype(creator())::element_type>::value,
                      "ConcreteType must derive from Base");

        // 将插件构造器注册到 PluginFactory 中。
        PluginFactory<Base>::instance().registerCreator(name, std::move(creator));
    }
};
