#include <Zone.hpp>
#include <iostream>

Zone::Zone(Type type, const sf::Vector2f& size): type(type), size(size) {}

sf::FloatRect Zone::getBoundingRect() const {
    sf::FloatRect rect;
    rect.left = getWorldPosition().x;
    rect.top = getWorldPosition().y;
    rect.width = size.x;
    rect.height = size.y;
    return rect;
}

sf::Vector2f Zone::getCenter() const {
    sf::FloatRect rect = getBoundingRect();
    return rect.getPosition() + rect.getSize() / 2.f;
}

bool Zone::isSafe() {
    return getType() == Type::Safe;
}

void Zone::setType(Type type) {
    this->type = type;
}

Zone::Type Zone::getType() {
    return type;
}

sf::Vector2f Zone::getSize() {
    return size;
}

void Zone::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    // sf::RectangleShape rect(size);
    // rect.setOutlineThickness(1);
    // if (type == Type::Dead)
    //     rect.setOutlineColor(sf::Color::Red);
    // else
    //     rect.setOutlineColor(sf::Color::Green);
    // rect.setFillColor(sf::Color::Transparent);
    // target.draw(rect, states);
}