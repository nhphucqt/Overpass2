#ifndef INTENT_HPP
#define INTENT_HPP

#include <memory>
#include <map>
#include <string>
#include <stdexcept>

class Intent {
public:
    typedef std::unique_ptr<Intent> Ptr;
    static const int NO_REQUEST_CODE = -1;

private:
    class IntentExtra {
    public:
        virtual ~IntentExtra() {}
    };
    template<typename T>

    class TypedIntentExtra: public IntentExtra {
    private:
        T value;
    public:
        TypedIntentExtra(T value): value(value) {}
        T getValue() { return value; }
    };

    std::map<std::string, std::unique_ptr<IntentExtra>> extras;
    int requestCode;

public:
    class Builder {
    private:
        std::unique_ptr<Intent> intent;
    public:
        Builder() {
            intent = std::make_unique<Intent>();
        }

        Builder& setRequestCode(int requestCode) {
            if (requestCode < 0) {
                throw std::runtime_error("Request code must be non-negative");
            }
            intent->setRequestCode(requestCode);
            return *this;
        }

        template<typename T>
        Builder& putExtra(std::string key, T value) {
            intent->putExtra(key, value);
            return *this;
        }

        std::unique_ptr<Intent> build() {
            return std::move(intent);
        }
    };

    Intent() {
        requestCode = NO_REQUEST_CODE;
    }

    void setRequestCode(int requestCode) {
        this->requestCode = requestCode;
    }

    int getRequestCode() {
        return requestCode;
    }

    template<typename T>
    void putExtra(std::string key, T value) {
        extras[key] = std::make_unique<TypedIntentExtra<T>>(value);
    }

    bool hasExtra(std::string key) {
        return extras.find(key) != extras.end();
    }

    template<typename T>
    T getExtra(std::string key) {
        return static_cast<TypedIntentExtra<T>*>(extras[key].get())->getValue();
    }

    template<typename T>
    T getExtra(std::string key, T defaultValue) {
        if (hasExtra(key)) {
            return getExtra<T>(key);
        } else {
            return defaultValue;
        }
    }
};

#endif