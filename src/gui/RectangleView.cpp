#include <SFML/Graphics.hpp>
#include <iostream>
#include <RectangleView.hpp>

RectangleView::RectangleView(EventPublisher* publisher, float left, float top, float width, float height)
: RectangleView(publisher, sf::Vector2f(width, height), sf::Vector2f(left, top), sf::Color::Black) {}

RectangleView::RectangleView(EventPublisher* publisher, float left, float top, float width, float height, const sf::Color& color)
: RectangleView(publisher, sf::Vector2f(width, height), sf::Vector2f(left, top), color) {}

RectangleView::RectangleView(EventPublisher* publisher, const sf::Vector2f& size, const sf::Vector2f& position)
: RectangleView(publisher, size, sf::Vector2f(0, 0), sf::Color::Black) {}

RectangleView::RectangleView(EventPublisher* publisher, const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color)
: ViewGroup(publisher), mRect(size) {
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

sf::FloatRect RectangleView::getGlobalBounds() const {
    return getWorldTransform().transformRect(mRect.getGlobalBounds());
}

bool RectangleView::isMouseHovering(const sf::Vector2f& mousePoint) const {
    return getGlobalBounds().contains(mousePoint);
}


bool RectangleView::isOnMouseButtonPressed(const sf::Event& event) const {
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}

bool RectangleView::isOnMouseButtonReleased(const sf::Event& event) const {
    return isMouseHovering(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
}