#ifndef TRAFFICLIGHT_HPP
#define TRAFFICLIGHT_HPP
#include <Entity.hpp>
#include <Obstacle.hpp>

class TrafficLight: public Entity {
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

#endif