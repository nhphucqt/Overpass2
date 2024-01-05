#include <ToggleButtonView.hpp>
#include <iostream>

ToggleButtonView::ToggleButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const char* text, unsigned int characterSize, const sf::Vector2f& position)
: ToggleButtonView(publisher, texture, font, textureRects, std::string(text), characterSize, position) {}

ToggleButtonView::ToggleButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string& text, unsigned int characterSize, const sf::Vector2f& position)
: ButtonView(publisher, texture, font, text, characterSize, position, textureRects[(int)ButtonType::OFF]) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
    }

    mIsOn = false;

    setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {});
}

ToggleButtonView::ToggleButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const char* text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: ToggleButtonView(publisher, texture, font, textureRects, std::string(text), characterSize, position, size) {}

ToggleButtonView::ToggleButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: ButtonView(publisher, texture, font, text, characterSize, position, textureRects[(int)ButtonType::OFF], size) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
    }

    mIsOn = false;

    setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {});
}

ToggleButtonView::ToggleButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position)
: ButtonView(publisher, texture, font, texts[0], characterSize, position, textureRects[(int)ButtonType::OFF]) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = texts[i];
        mTextureRects[i] = textureRects[i];
    }

    mIsOn = false;

    setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {});
}

ToggleButtonView::ToggleButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: ButtonView(publisher, texture, font, texts[0], characterSize, position, textureRects[(int)ButtonType::OFF], size) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = texts[i];
        mTextureRects[i] = textureRects[i];
    }

    mIsOn = false;

    setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {});
}

void ToggleButtonView::setOnMouseButtonReleased(EventCallback onMouseButtonReleased) {
    EventListener::EventDoubleCallback onDoubleEvent = [this](EventListener* listener, const sf::Event& event, EventCallback callback) {
        this->toggleState();
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(onEvent);
}

void ToggleButtonView::setState(bool isOn) {
    mIsOn = isOn;
    if (mIsOn) {
        this->setTextureRect(mTextureRects[(int)ButtonType::ON]);
        this->setText(mTexts[(int)ButtonType::ON]);
    } else {
        this->setTextureRect(mTextureRects[(int)ButtonType::OFF]);
        this->setText(mTexts[(int)ButtonType::OFF]);
    }
}

void ToggleButtonView::toggleState() {
    setState(!mIsOn);
}

int ToggleButtonView::getState() const {
    return mIsOn;
}