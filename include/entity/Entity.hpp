#ifndef ENTITY
#define ENTITY
#include <SFML/Graphics.hpp>

class Entity: sf::Drawable, sf::Transformable {
    private:
        sf::Sprite sprite;
    protected:
        sf::Vector2f velocity;
    public:
        Entity(sf::Texture texture);
        Entity(sf::Texture texture, float vx, float vy);
        Entity(sf::Texture texture, sf::Vector2f v);
        void setVelocity(sf::Vector2f velocity);
        sf::Vector2f getVelocity();
        bool checkCollision(Entity& other);
        sf::FloatRect getGlobalBounds();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Vector2f center();
};

// obstacles are entities that player cannot touch, including normal "vehicles"
class Obstacle: Entity {
    private:
    public:
        Obstacle(sf::Texture texture);
        Obstacle(sf::Texture texture, float vx, float vy);
        Obstacle(sf::Texture texture, sf::Vector2f v);
        void move(sf::Time delta); // make small steps, should be used in a loop, distance moved = delta * velocity
        void move(); // call the above function with delta equals 1/60s (60 fps)
};

class TrafficLight: Entity {
    public:
        enum class TrafficColor {Red, Yellow, Green};
    private:
        TrafficColor current;
        sf::Time red;
        sf::Time yellow;
        sf::Time green;
        sf::Clock clock;
        void initInterval(float r, float y, float g);
    public:
        TrafficLight(sf::Texture texture, float interval);
        TrafficLight(sf::Texture texture, TrafficColor initColor, float interval);
        TrafficLight(sf::Texture texture, float r, float y, float g);
        TrafficLight(sf::Texture texture, TrafficColor initColor, float r, float y, float g);
        bool trafficAllow();
};

// vehicles are entities that can be ridden on: logs, animals, player's vehicles, etc
class Vehicle: Entity {
    private:
        int health; // times of collision before destroyed
        sf::Time interval; // interval of existance
    public:
        Vehicle(sf::Texture texture);
        Vehicle(sf::Texture texture, float t);
        Vehicle(sf::Texture texture, int hp);
        bool isRidden(Entity& other);
        bool isDestroyed();
        bool collides(); // minus health, health = 0 when collides with river
};

#endif
