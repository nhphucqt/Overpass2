#include <Zone.hpp>

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

void Zone::attachView(ViewGroup::Ptr view) {
    view->setPosition(getCenter());
    ViewGroup::attachView(std::move(view));
}

bool Zone::isSafe() {
    return type == Type::Safe;
}

void Zone::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
}