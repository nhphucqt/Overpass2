#include <Viewable.hpp>

Viewable::Viewable(): parent(nullptr) {}

Viewable* Viewable::getParent() {
    return parent;
}

void Viewable::setParent(Viewable* parent) {
    this->parent = parent;
}