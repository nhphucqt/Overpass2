#ifndef VECTOR_2D_UTILS_HPP
#define VECTOR_2D_UTILS_HPP

#include <SFML/System/Vector2.hpp>

class Vector2dUtils {
public:
    static float length(sf::Vector2f vector);
    static float distance(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
    static sf::Vector2f unitVector(sf::Vector2f vector);
};

#endif