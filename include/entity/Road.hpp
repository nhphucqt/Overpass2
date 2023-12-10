#ifndef ROAD_HPP
#define ROAD_HPP

#include <Lane.hpp>
#include <TrafficLight.hpp>
#include <Animal.hpp>
#include <Vehicle.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Road: public Lane {
public:
    Road(TextureManager* textures, bool isReverse = false);

private:
	std::vector<Vehicle *> cars;
	std::vector<Animal *> animals;
    TrafficLight* trafficlight;

    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif