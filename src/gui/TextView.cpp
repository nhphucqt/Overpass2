#include <TextView.hpp>
#include <cassert>
#include <iostream>

TextView::TextView(const std::string& text, const sf::Font& font)
: TextView(text, font, sf::Vector2f(0, 0)) {}

TextView::TextView(const std::string& text, const sf::Font& font, const sf::Vector2f& position)
: TextView(text, font, position, 30) {}

TextView::TextView(const std::string& text, const sf::Font& font, const sf::Vector2f& position, unsigned int characterSize)
: TextView(text, font, position, characterSize, sf::Color::Black) {}

TextView::TextView(const std::string& text, const sf::Font& font, const sf::Vector2f& position, unsigned int characterSize, const sf::Color& color): text(text, font, characterSize) {
    setPosition(position);
    setFillColor(color);
}

void TextView::setText(const std::string& text) {
    this->text.setString(text);
}

void TextView::setFillColor(const sf::Color& color) {
    text.setFillColor(color);
}

std::string TextView::getText() const {
    return text.getString();
}

sf::FloatRect TextView::getGlobalBounds() const {
    return getTransform().transformRect(text.getGlobalBounds());
}

void TextView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text, states);
}

bool TextView::isOnMouseButtonPressed(const sf::Event& event) const {
    return getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
}

bool TextView::isOnMouseButtonReleased(const sf::Event& event) const {
    return text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
}