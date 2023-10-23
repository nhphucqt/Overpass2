#include <RectangleView.hpp>


RectangleView::RectangleView(): Viewable() {
    std::mt19937 rng(time(nullptr));
    int x = rng() % 700;
    int y = rng() % 500;
    rect = sf::RectangleShape(sf::Vector2f(100, 100));
    rect.setPosition(x, y);
    rect.setFillColor(sf::Color::Red);
}

RectangleView::RectangleView(Viewable* parent): Viewable(parent) {
    rect = sf::RectangleShape(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Red);
}

RectangleView::RectangleView(Viewable* parent, sf::Vector2f dimens): Viewable(parent, dimens) {
    rect = sf::RectangleShape(dimens);
    rect.setFillColor(sf::Color::Red);
}

void RectangleView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(rect, states);
}