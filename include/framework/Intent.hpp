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
    static const int ACTION_NONE = -1;

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
    int action;

public:
    class Builder {
    private:
        std::unique_ptr<Intent> intent;
    public:
        Builder() {
            intent = std::make_unique<Intent>();
        }

        Builder& setAction(int action) {
            if (action < 0) {
                throw std::runtime_error("Action must be non-negative");
            }
            intent->setAction(action);
            return *this;
        }

        Builder& setRequestCode(int requestCode) {
            if (requestCode < 0) {
                throw std::runtime_error("Request code must be non-negative");
            }
            intent->setRequestCode(requestCode);
            return *this;
        }

        template<typename T>
        Builder& putExtra(const std::string& key, T value) {
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

    void setAction(int action) {
        if (action < 0) {
            throw std::runtime_error("Action must be non-negative");
        }
        this->action = action;
    }

    int getAction() {
        return action;
    }

    void setRequestCode(int requestCode) {
        if (requestCode < 0) {
            throw std::runtime_error("Request code must be non-negative");
        }
        this->requestCode = requestCode;
    }

    int getRequestCode() {
        return requestCode;
    }

    template<typename T>
    void putExtra(const std::string& key, T value) {
        extras[key] = std::make_unique<TypedIntentExtra<T>>(value);
    }

    bool hasExtra(const std::string& key) {
        return extras.find(key) != extras.end();
    }

    template<typename T>
    T getExtra(const std::string& key, T defaultValue) {
        if (hasExtra(key)) {
            return getExtra<T>(key);
        } else {
            return defaultValue;
        }
    }

    template<typename T>
    T getExtra(const std::string& key) {
        if (hasExtra(key)) {
            return static_cast<TypedIntentExtra<T>*>(extras[key].get())->getValue();
        } else {
            throw std::runtime_error("No extra with key " + key);
        }
    }
};

#endif