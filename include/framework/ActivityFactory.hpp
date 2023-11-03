#ifndef ACTIVITY_FACTORY_HPP
#define ACTIVITY_FACTORY_HPP

#include <memory>

template<typename T>
class ActivityFactory {
public:
    static std::unique_ptr<T> createInstance() {
        std::unique_ptr<T> activity = std::make_unique<T>();
        return std::move(activity);
    }
};

#endif