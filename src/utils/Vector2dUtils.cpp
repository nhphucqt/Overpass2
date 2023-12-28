#include <Vector2dUtils.hpp>

#include <cmath>
#include <cassert>

float Vector2dUtils::length(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Vector2dUtils::distance(const sf::Vector2f& lhs, const sf::Vector2f& rhs) {
    return length(lhs - rhs);
}

sf::Vector2f Vector2dUtils::unitVector(sf::Vector2f vector) {
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / length(vector);
}