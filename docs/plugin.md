# 插件注册机制

本模块整体实现了一个 插件化组件注册机制，结合了多种设计模式，包括：

- 单例模式（Singleton）
- 工厂模式（Factory）
- 注册器模式（Registry）
- 宏元编程（Compile-time Plugin Registration）
- 强制链接机制（Force Link Symbol）

## 模块结构与职责划分

| 模块路径                        | 模块名                 | 职责描述                                                |
|-----------------------------|---------------------|-----------------------------------------------------|
| `source/plugin`             | `plugin_factory`    | 提供通用插件注册与创建框架，包含 `PluginFactory` 与 `PluginRegistry` |
| `source/iface/user`         | `iface_user`        | 定义 `IUserManager` 接口及其插件工厂声明                        |
| `source/impls/user/default` | `impl_user_default` | 提供 `DefaultUserManager` 实现类，并通过注册宏将其实例注册到插件工厂       |

## 设计模式

### 单例模式（Singleton）

```cpp

static PluginFactory& instance() {
    static PluginFactory factory;
    return factory;
}

```

- 保证 PluginFactory<Base> 的全局唯一性
- 用于集中管理所有插件注册表，避免重复实例化
- 利用 C++11 的 thread-safe static 局部变量实现，无需手动加锁

### 工厂模式（Factory）

```cpp

using Creator = std::function<std::shared_ptr<Base>()>;
std::shared_ptr<Base> create(const std::string& typeName);

```

- 通过注册字符串 → 构造函数映射的 Creator 实现对象的解耦创建
- 调用者无需知道具体类名，只需提供 typeName 即可创建实例

### 注册器模式（Registry）

```cpp

void registerCreator(const std::string& typeName, Creator creator);

```

- 将 typeName 映射为 Creator
- 所有注册行为封装在宏 REGISTER_PLUGIN() 中，用户只需一行代码即可注册插件

### 宏元编程 + 链接符号注册机制（Force Link）

#### 注册插件

```cpp

REGISTER_PLUGIN(IUserManager, DefaultUserManager, USER_MANAGER_FACTORY_NAME)

```

展开后逻辑为：

- 静态对象构造时将 DefaultUserManager 注册到 PluginFactory<IUserManager> 中
- 利用 C++ 的静态对象初始化顺序来触发注册

#### 链接保持

```cpp

DECLARE_FORCE_LINK_SYMBOL(USER_MANAGER_FACTORY_CLASS)
DEFINE_FORCE_LINK_SYMBOL(USER_MANAGER_FACTORY_CLASS)
FORCE_LINK_CALL(USER_MANAGER_FACTORY_CLASS)

```

目的：

- 避免由于插件类未被主动引用而在链接时被优化掉
- 使用 extern "C" 和 __attribute__((used)) 机制保留符号

#### 接口隔离 + 动态多态

```cpp

class IUserManager {
    virtual bool validateUser(const User& user) = 0;
};

```

- 提供用户认证的抽象接口
- 允许多个实现（插件）并存，调用方只关心接口而无需关心具体实现类

## 实现细节与行为链

### 插件注册流程

- REGISTER_PLUGIN() 宏定义触发静态结构体构造，注册插件
- 插件注册表记录 typeName 与对应构造函数（Creator）
- 插件调用方通过 FactoryClass::instance().create("default") 实例化

### 模块层分离

| 角色       | 内容        | 示例                                                     |
|----------|-----------|--------------------------------------------------------|
| **接口模块** | 声明插件工厂    | `DECLARE_PLUGIN_FACTORY(...)`                          |
| **实现模块** | 注册插件      | `REGISTER_PLUGIN(...)`、`DEFINE_FORCE_LINK_SYMBOL(...)` |
| **使用方**  | 调用插件工厂实例化 | `UserManagerFactory::instance().create(...)`           |

## 模块化设计优点

| 优点           | 说明                                       |
|--------------|------------------------------------------|
| **解耦合**      | 实现与接口完全分离，新增插件无需修改现有代码                   |
| **模块自治**     | 每个实现插件只需注册自己，避免集中管理注册表                   |
| **运行时扩展性**   | 支持根据字符串 ID 动态创建对象，便于配置驱动行为               |
| **代码复用性强**   | `PluginFactory<T>` 可支持任意接口的插件机制          |
| **链接保活机制完善** | 使用强制链接手段，确保静态注册不被链接器优化                   |
| **线程安全**     | 插件注册与创建都使用 `std::scoped_lock` 加锁，保证多线程安全 |

## 使用示例

```cpp

auto userManager = UserManagerFactory::instance().create("default");
if (userManager) {
    userManager->validateUser(someUser);
}

```

通过字符串 "default" 获取 DefaultUserManager 实例，不直接依赖其头文件，解耦性强，利于插件扩展或热替换。

## 总结

本套机制是一个高度抽象化、插件化、模块化的运行时对象工厂方案，广泛适用于：

- 接口与实现解耦场景
- 动态注册插件系统
- 支持热更新或可插拔组件设计

结合 工厂 + 单例 + 注册器 + 链接符号保活 + 宏编程，该机制在保持性能与可维护性的同时，提供了极高的扩展能力，非常适合在大型系统中构建灵活可扩展的插件架构。
