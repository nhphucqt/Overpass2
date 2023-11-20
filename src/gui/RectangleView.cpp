#include <SFML/Graphics.hpp>
#include <iostream>
#include <RectangleView.hpp>

RectangleView::RectangleView(float left, float top, float width, float height)
: RectangleView(sf::Vector2f(width, height), sf::Vector2f(left, top), sf::Color::Black) {}

RectangleView::RectangleView(float left, float top, float width, float height, const sf::Color& color)
: RectangleView(sf::Vector2f(width, height), sf::Vector2f(left, top), color) {}

RectangleView::RectangleView(const sf::Vector2f& size, const sf::Vector2f& position)
: RectangleView(size, sf::Vector2f(0, 0), sf::Color::Black) {}

RectangleView::RectangleView(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color): mRect(size) {
    setPosition(position);
    setFillColor(color);
}

sf::Vector2f RectangleView::getSize() {
    return mRect.getSize();
}

void RectangleView::setFillColor(sf::Color color) {
    mRect.setFillColor(color);
}

void RectangleView::setSize(const sf::Vector2f& size) {
    mRect.setSize(size);
}

void RectangleView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mRect, states);
}

bool RectangleView::isOnMouseButtonPressed(const sf::Event& event) const {
    sf::Vector2i pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
    sf::Vector2f position = getPosition();
    sf::Vector2f size = mRect.getSize();
    return pos.x >= position.x && pos.x <= position.x + size.x
        && pos.y >= position.y && pos.y <= position.y + size.y;
}

bool RectangleView::isOnMouseButtonReleased(const sf::Event& event) const {
    sf::Vector2i pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
    sf::Vector2f position = getPosition();
    sf::Vector2f size = mRect.getSize();
    return pos.x >= position.x && pos.x <= position.x + size.x
        && pos.y >= position.y && pos.y <= position.y + size.y;
}