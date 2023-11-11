#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include <Entity.hpp>

// obstacles are entities that player cannot touch, including normal "vehicles"
class Obstacle: public Entity {
    private:
        const EntityType TYPE = EntityType::Obstacle;
        bool isAnimal; // animals move even when traffic light is red
    public:
        Obstacle(sf::Texture texture, bool animal = false);
        Obstacle(sf::Texture texture, float vx, float vy, bool animal = false);
        Obstacle(sf::Texture texture, sf::Vector2f v, bool animal = false);
        void move(); // call the above function with delta equals 1/60s (60 fps)
        bool checkAnimal() const;
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif