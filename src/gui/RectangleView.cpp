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