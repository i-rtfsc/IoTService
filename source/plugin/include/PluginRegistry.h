#pragma once

// =======================================
// C / C++ extern 兼容处理
// C / C++ extern compatibility macros
// =======================================
#ifdef __cplusplus
#define BEGIN_EXTERN_C extern "C" {
#define END_EXTERN_C }
#else
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif

// =======================================
// 强制链接符号命名拼接宏
// Macros for force-link symbol naming
// =======================================
#define _FORCE_LINK_SYMBOL_NAME(name) force_link_##name
#define FORCE_LINK_SYMBOL_NAME(name) _FORCE_LINK_SYMBOL_NAME(name)

// =======================================
// 强制链接调用宏
// Macros for calling force-link functions
// =======================================
#define _FORCE_LINK_CALL(name) force_link_##name()
#define FORCE_LINK_CALL(name) _FORCE_LINK_CALL(name)

// =======================================
// 声明一个外部符号用于强制链接保留
// Declare an external function to preserve symbol during linking
// =======================================
#define DECLARE_FORCE_LINK_SYMBOL(name)  \
    BEGIN_EXTERN_C                       \
    void FORCE_LINK_SYMBOL_NAME(name)(); \
    END_EXTERN_C

// =======================================
// 定义一个空函数用于触发链接符号保留
// Define a no-op function to enforce symbol retention
// =======================================
#define DEFINE_FORCE_LINK_SYMBOL(name) \
    extern "C" void FORCE_LINK_SYMBOL_NAME(name)() {}

// =======================================
// 注册插件宏（模板类型 + 插件类型 + 名称）
// Macro to register a plugin with factory (BaseType, ConcreteType, name)
// =======================================
#define REGISTER_PLUGIN(BaseType, ConcreteType, name)                              \
    namespace {                                                                    \
    struct Register##ConcreteType {                                                \
        Register##ConcreteType() {                                                 \
            static_assert(std::is_base_of<BaseType, ConcreteType>::value,          \
                          "ConcreteType must derive from BaseType");               \
            static_assert(std::is_convertible<decltype(name), const char*>::value, \
                          "name must be a string literal");                        \
            ::PluginFactory<BaseType>::instance().registerCreator(                 \
                name, []() {                                                       \
                    return std::make_shared<ConcreteType>();                       \
                });                                                                \
        }                                                                          \
    };                                                                             \
    static Register##ConcreteType _register_##ConcreteType;                        \
    }

// =======================================
// 声明插件工厂包装类并触发链接符号
// Declare plugin factory wrapper class and force link call
// =======================================
#define DECLARE_PLUGIN_FACTORY(BaseType, FactoryClass, LinkName) \
    class FactoryClass {                                         \
    public:                                                      \
        static ::PluginFactory<BaseType>& instance() {           \
            FORCE_LINK_CALL(LinkName);                           \
            return ::PluginFactory<BaseType>::instance();        \
        }                                                        \
    }
