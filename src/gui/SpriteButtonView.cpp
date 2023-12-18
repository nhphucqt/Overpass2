#include <SpriteButtonView.hpp>
#include <iostream>

SpriteButtonView::SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const char* text, unsigned int characterSize, const sf::Vector2f& position)
: SpriteButtonView(publisher, texture, font, textureRects, std::string(text), characterSize, position) {}

SpriteButtonView::SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string& text, unsigned int characterSize, const sf::Vector2f& position)
: ButtonView(texture, font, text, characterSize, position, textureRects[(int)ButtonType::NORMAL]) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
    }

    setOnMouseButtonPressed(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseButtonReleased(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseMoved(publisher, [&](EventListener* listener, const sf::Event& event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const char* text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: SpriteButtonView(publisher, texture, font, textureRects, std::string(text), characterSize, position, size) {}

SpriteButtonView::SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: ButtonView(texture, font, text, characterSize, position, textureRects[(int)ButtonType::NORMAL], size) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = text;
        mTextureRects[i] = textureRects[i];
    }

    setOnMouseButtonPressed(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseButtonReleased(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseMoved(publisher, [&](EventListener* listener, const sf::Event& event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position)
: ButtonView(texture, font, texts[0], characterSize, position, textureRects[(int)ButtonType::NORMAL]) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = texts[i];
        mTextureRects[i] = textureRects[i];
    }

    setOnMouseButtonPressed(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseButtonReleased(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseMoved(publisher, [&](EventListener* listener, const sf::Event& event) {});
}

SpriteButtonView::SpriteButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const sf::IntRect* textureRects, const std::string* texts, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: ButtonView(texture, font, texts[0], characterSize, position, textureRects[(int)ButtonType::NORMAL], size) {
    for (int i = 0; i < (int)ButtonType::COUNT; i++) {
        mTexts[i] = texts[i];
        mTextureRects[i] = textureRects[i];
    }

    setOnMouseButtonPressed(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseButtonReleased(publisher, [&](EventListener* listener, const sf::Event& event) {});
    setOnMouseMoved(publisher, [&](EventListener* listener, const sf::Event& event) {});
}

void SpriteButtonView::setOnMouseButtonPressed(EventPublisher* publisher, EventCallback onMouseButtonPressed) {
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventCallback callback) {
        this->setTextureRect(mTextureRects[(int)ButtonType::PRESSED]);
        this->setText(mTexts[(int)ButtonType::PRESSED]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonPressed);
    EventListener::setOnMouseButtonPressed(publisher, onEvent);
}

void SpriteButtonView::setOnMouseButtonReleased(EventPublisher* publisher, EventCallback onMouseButtonReleased) {
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventCallback callback) {
        this->setTextureRect(mTextureRects[(int)ButtonType::HOVERING]);
        this->setText(mTexts[(int)ButtonType::HOVERING]);
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseButtonReleased);
    EventListener::setOnMouseButtonReleased(publisher, onEvent);
}

void SpriteButtonView::setOnMouseMoved(EventPublisher* publisher, EventCallback onMouseMoved) {
    EventListener::EventDoubleCallback onDoubleEvent = [&](EventListener* listener, const sf::Event& event, EventCallback callback) {
        if (this->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Right) ||
                sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                    this->setTextureRect(mTextureRects[(int)ButtonType::PRESSED]);
                    this->setText(mTexts[(int)ButtonType::PRESSED]);
            } else {
                this->setTextureRect(mTextureRects[(int)ButtonType::HOVERING]);
                this->setText(mTexts[(int)ButtonType::HOVERING]);
            }
        } else {
            this->setTextureRect(mTextureRects[(int)ButtonType::NORMAL]);
            this->setText(mTexts[(int)ButtonType::NORMAL]);
        }
        callback(listener, event);
    };
    EventListener::EventCallback onEvent = std::bind(onDoubleEvent, std::placeholders::_1, std::placeholders::_2, onMouseMoved);
    EventListener::setOnMouseMoved(publisher, onEvent);
}