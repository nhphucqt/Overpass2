#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include <unordered_map>
#include <stdexcept>
#include <string>
#include <utility>

#include <SFML/System/Vector2.hpp>

#include <ConfigKey.hpp>

class ConfigValue {
public:
    virtual ~ConfigValue() = default;
};

template <typename T>
class TypedConfigValue : public ConfigValue {
public:
    TypedConfigValue(const T &value);
    T getValue() const;

private:
    T mValue;
};

class ConfigNotFound : public std::runtime_error {
public:
    ConfigNotFound(const ConfigKey key);
};

class AppConfig {
public:
    static AppConfig &getInstance();

    template <typename T>
    T get(const ConfigKey key) const;

    template <typename T>
    void set(const ConfigKey key, const T &value);

private:
    std::unordered_map<ConfigKey, ConfigValue *> mConfigs;

    AppConfig(const AppConfig &) = delete;
    AppConfig &operator=(const AppConfig &) = delete;

    AppConfig();
    ~AppConfig();
};

#include <AppConig.inl>

#endif