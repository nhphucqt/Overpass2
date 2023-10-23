#include <Viewable.hpp>

Viewable::Viewable(): parent(nullptr), dimens(sf::Vector2f(0, 0)) {}
Viewable::Viewable(Viewable* parent): parent(parent), dimens(sf::Vector2f(0, 0)) {}
Viewable::Viewable(Viewable* parent, sf::Vector2f dimens): parent(parent), dimens(dimens) {}

Viewable* Viewable::getParent() {
    return parent;
}

void Viewable::setParent(Viewable* parent) {
    this->parent = parent;
}

sf::Vector2f Viewable::getDimens() {
    return dimens;
}

void Viewable::setDimens(sf::Vector2f dimens) {
    this->dimens = dimens;
}