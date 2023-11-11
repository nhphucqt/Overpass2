#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <Entity.hpp>

const float INTERVAL = 3600; // use for default interval of existence Vehicle

// vehicles are entities that can be ridden on on land: animals, player's vehicles, etc
class Vehicle: public Entity {
    private:
        const EntityType TYPE = EntityType::Vehicle;
        int health; // times of collision before destroyed
        sf::Time interval; // interval of existance
    public:
        Vehicle(sf::Texture texture);
        Vehicle(sf::Texture texture, float t);
        Vehicle(sf::Texture texture, int hp);
        bool isRidden(Entity& other);
        bool isDestroyed();
        bool collides(); // minus health, health = 0 when collides with river
        void move();
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif