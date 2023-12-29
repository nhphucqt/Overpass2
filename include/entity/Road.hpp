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
    static constexpr float laneLength = 1400.f;
    static constexpr float padding = 100.f;
    static const int numOfVehicle = 2, numOfAnimal = 1;
    static constexpr float vehicleVelocity = 300.f;
    static constexpr float vehicleSlowVelocity = 100.f;
    static constexpr float animalVelocity = 200.f;
    static constexpr float trafficLightPosition = 400.f;

	std::vector<Vehicle *> vehicles;
	std::vector<Animal *> animals;
    TrafficLight* trafficlight;

    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif