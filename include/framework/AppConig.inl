#include <AppConfig.hpp>

template <typename T>
inline TypedConfigValue<T>::TypedConfigValue(const T &value)
    : mValue(value)
{
}

template <typename T>
inline T TypedConfigValue<T>::getValue() const
{
    return mValue;
}

inline ConfigNotFound::ConfigNotFound(const ConfigKey key)
    : std::runtime_error("Config key not found " + std::to_string(static_cast<int>(key)))
{
}

inline AppConfig &AppConfig::getInstance()
{
    static AppConfig instance;
    return instance;
}

template <typename T>
inline T AppConfig::get(const ConfigKey key) const
{
    if (mConfigs.count(key) > 0)
    {
        const ConfigValue *configValue = mConfigs.at(key);
        if (const TypedConfigValue<T> *typedConfigValue = dynamic_cast<const TypedConfigValue<T> *>(configValue))
            return typedConfigValue->getValue();
    }
    throw ConfigNotFound(key);
}

template <typename T>
inline void AppConfig::set(const ConfigKey key, const T &value)
{
    mConfigs[key] = new TypedConfigValue<T>(value);
}

inline AppConfig::~AppConfig()
{
    for (auto &pair : mConfigs)
        delete pair.second;
}

inline AppConfig::AppConfig()
{
    set(ConfigKey::AppName, std::string("Overpass"));
    set(ConfigKey::WindowSize, std::pair<int, int>(1280, 720));
    set(ConfigKey::FPS, int(60));
}