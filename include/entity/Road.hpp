#ifndef ROAD_HPP
#define ROAD_HPP

#include <fstream>
#include <iostream>
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
    Road(TextureManager* textures, bool isReverse = false, bool isLoad = false);
    unsigned int getCategory() const;

private:
	std::vector<Vehicle *> cars;
	std::vector<Animal *> animals;
    TrafficLight* trafficlight;

    void updateCurrent(sf::Time dt);
    void buildLane();

private:
    struct RoadData {
        std::vector<Vehicle::VehicleData> vehicles;
        std::vector<Animal::AnimalData> animals;
    };

public:
    void saveLaneData(const std::string& filename) override;
    void loadLaneData(const std::string& filename) override;
    
};

#endif