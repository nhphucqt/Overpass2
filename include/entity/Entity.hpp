#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include <ViewGroup.hpp>

const int FPS = 60;

class Entity: public ViewGroup {
    public:
        enum class EntityType {Entity, Obstacle, TrafficLight, Vehicle, Log};
    private:
        const EntityType TYPE = EntityType::Entity;
        // void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vector2f velocity;
    protected:
        sf::Sprite sprite;
        void move(sf::Time delta);
    public:
        Entity(sf::Texture texture);
        Entity(sf::Texture texture, float vx, float vy);
        Entity(sf::Texture texture, sf::Vector2f v);
        void setVelocity(sf::Vector2f velocity);
        sf::Vector2f getVelocity();
        bool checkCollision(Entity& other);
        sf::FloatRect getGlobalBounds();
        sf::Vector2f center();
        EntityType getType();
};

#endif
