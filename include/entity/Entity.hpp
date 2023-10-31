#ifndef ENTITY
#define ENTITY
#include <SFML/Graphics.hpp>
#include "../framework/ViewGroup.hpp"

class Entity: ViewGroup {
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

// obstacles are entities that player cannot touch, including normal "vehicles"
class Obstacle: Entity {
    private:
        const EntityType TYPE = EntityType::Obstacle;
        bool isAnimal; // animals move even when traffic light is red
    public:
        Obstacle(sf::Texture texture, bool animal = false);
        Obstacle(sf::Texture texture, float vx, float vy, bool animal = false);
        Obstacle(sf::Texture texture, sf::Vector2f v, bool animal = false);
        void move(sf::Time delta); // make small steps, should be used in a loop, distance moved = delta * velocity
        void move(); // call the above function with delta equals 1/60s (60 fps)
        bool checkAnimal() const;
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

class TrafficLight: Entity {
    public:
        enum class TrafficColor {Red, Yellow, Green};
    private:
        const EntityType TYPE = EntityType::TrafficLight;
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
        bool trafficAllow(const Obstacle& other);
        bool trafficAllow(const Entity& other);
        bool trafficAllow();
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

// vehicles are entities that can be ridden on on land: animals, player's vehicles, etc
class Vehicle: Entity {
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
        void move(sf::Time delta); // make small steps, should be used in a loop, distance moved = delta * velocity
        void move();
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

// the only entity that is not destroyed in river
class Log: Entity {
    public:
        enum class LogType {Harmful, Harmless}; // crocodile is a harmful log
        Log(sf::Texture texture, LogType log = LogType::Harmless);
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        LogType getLogType();
    private:
        const EntityType TYPE = EntityType::Log;
        LogType logType;
};

#endif
