#ifndef TRAFFICLIGHT_HPP
#define TRAFFICLIGHT_HPP
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Duration {
    const sf::Time Red = sf::seconds(3);
    const sf::Time Yellow = sf::seconds(1);
    const sf::Time Green = sf::seconds(3);
};

class TrafficLight: public Entity {
public:
    struct TrafficLightData {
        int currentColor;
        float elapsedTime;
    };

    enum class Color{Red, Yellow, Green};
    TrafficLight(const TextureHolder& textures);
    Color getCurrentColor();
    void setDuration(int red = 1, int yellow = 1, int green = 1);

    bool isRed();
    bool isYellow();
    bool isGreen();

    TrafficLightData serialize() const;
    void deserialize(const TrafficLightData& data);

private:
    sf::IntRect rect;
    Color current;
    sf::Time red;
    sf::Time yellow;
    sf::Time green;
    sf::Time elapsed;
    void updateCurrent(sf::Time dt);
    void updateCurrentColor(sf::Time dt);
};

#endif