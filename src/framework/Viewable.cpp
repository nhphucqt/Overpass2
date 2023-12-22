#include <Viewable.hpp>

Viewable::Viewable(): parent(nullptr) {}

Viewable* Viewable::getParent() const {
    return parent;
}

void Viewable::setParent(Viewable* parent) {
    this->parent = parent;
}

void Viewable::update(sf::Time delta) {
    // do nothing
}

sf::Transform Viewable::getAbsoluteTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const Viewable* viewable = this; viewable != nullptr; viewable = viewable->getParent()) {
        transform = viewable->getTransform() * transform;
    }
    return transform;
}

void Viewable::onCommand(const Command &command, sf::Time dt) {
}