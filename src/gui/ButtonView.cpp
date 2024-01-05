#include <ButtonView.hpp>
#include <iostream>

ButtonView::ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text)
: ButtonView(publisher, texture, font, text, sf::Vector2f(0, 0)) {}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position)
: ButtonView(publisher, texture, font, text, position, sf::Vector2f(texture.getSize())) {}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size)
: ButtonView(publisher, texture, font, text, 30, position, size) {}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size)
: ViewGroup(publisher), mSprite(texture), mRect(size), mText(text, font, characterSize) {
    setPosition(position);
    mRect.setFillColor(sf::Color::Transparent);
    mSprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size/2.f);
}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::IntRect& textureRect)
: ViewGroup(publisher), mSprite(texture, textureRect), mRect(sf::Vector2f(textureRect.width, textureRect.height)), mText(text, font, characterSize) {
    setPosition(position);
    mRect.setFillColor(sf::Color::Transparent);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(textureRect.width/2, textureRect.height/2);
}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Texture& texture, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::IntRect& textureRect, const sf::Vector2f& size)
: ViewGroup(publisher), mSprite(texture, textureRect), mRect(size), mText(text, font, characterSize) {
    setPosition(position);
    mRect.setFillColor(sf::Color::Transparent);
    // mRect.setFillColor(sf::Color::Red);
    mSprite.setScale(size.x / textureRect.width, size.y / textureRect.height);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size/2.f);
}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& size, const sf::Color& fillColor)
: ButtonView(publisher, font, text, 30, sf::Vector2f(0, 0), size, fillColor) {}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor)
: ButtonView(publisher, font, text, 30, position, size, fillColor) {}

ButtonView::ButtonView(EventPublisher* publisher, const sf::Font& font, const std::string& text, unsigned int characterSize, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& fillColor)
: ViewGroup(publisher), mSprite(), mRect(size), mText(text, font, characterSize) {
    setPosition(position);
    mRect.setFillColor(fillColor);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(size/2.f);
}

void ButtonView::setTexture(const sf::Texture& texture, bool resetRect) {
    mSprite.setTexture(texture, resetRect);
    // mRect.setSize(sf::Vector2f(texture.getSize()));
}

void ButtonView::setTextureRect(const sf::IntRect& rect) {
    mSprite.setTextureRect(rect);
    // mRect.setSize(sf::Vector2f(rect.width, rect.height));
}

void ButtonView::setText(const std::string& text) {
    mText.setString(text);
    mText.setOrigin(0, 0);
    mText.setPosition(0, 0);
    mText.setOrigin(mText.getGlobalBounds().getPosition() + mText.getGlobalBounds().getSize() / 2.f);
    mText.setPosition(mRect.getSize()/2.f);
}

void ButtonView::setBackGroundColor(const sf::Color& color) {
    mRect.setFillColor(color);
}

void ButtonView::setTextColor(const sf::Color& color) {
    mText.setFillColor(color);
}

sf::FloatRect ButtonView::getGlobalBounds() const {
    return getWorldTransform().transformRect(mRect.getGlobalBounds());
}

bool ButtonView::isMouseHovering(const sf::Vector2f& mousePoint) const {
    return getGlobalBounds().contains(mousePoint);
}

void ButtonView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mRect, states);
    target.draw(mSprite, states);
    target.draw(mText, states);
}

bool ButtonView::isOnMouseButtonPressed(const sf::Event& event) const {
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

bool ButtonView::isOnMouseButtonReleased(const sf::Event& event) const {
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

bool ButtonView::isOnMouseMoved(const sf::Event& event) const {
    return true;
}