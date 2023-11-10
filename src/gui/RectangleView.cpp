#include <SFML/Graphics.hpp>
#include <iostream>
#include <RectangleView.hpp>

RectangleView::RectangleView(int width, int height): mRect(sf::Vector2f(width, height)) {
    int x = rand() % (800 - width);
    int y = rand() % (600 - height);
    setPosition(x, y);
    mRect.setPosition(0, 0);
    mRect.setFillColor(sf::Color::Red);

    sf::Vector2f pos = getPosition();
}

sf::Vector2f RectangleView::getSize() {
    return mRect.getSize();
}

void RectangleView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(mRect, states);
}

void RectangleView::setFillColor(sf::Color color) {
    mRect.setFillColor(color);
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