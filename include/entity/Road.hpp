#ifndef ROAD_HPP
#define ROAD_HPP

#include <Lane.hpp>
#include <TrafficLight.hpp>
#include <Animal.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TrafficLight.hpp>
#include <Vehicle.hpp>

class Road : public Lane
{
public:
    Road(TextureManager *textures, bool isReverse, unsigned int vehicles_cnt,
         unsigned int animals_cnt, Vehicle::Type vehicle_type,
         Animal::Type animal_type, float velocity, bool isLoad = false);

    void setNumOfVehicle(int n);
    void setNumOfAnimal(int n);
    void setVehicleVelocity(float v);
    void setVehicleSlowVelocity(float v);
    void setAnimalVelocity(float v);
    void setTrafficLightPosition(float position);

private:
    float laneLength;
    float padding;
    int numOfVehicle;
    int numOfAnimal;
    float vehicleVelocity;
    float vehicleSlowVelocity;
    float animalVelocity;
    float trafficLightPosition;
    Animal::Type animalType;
    Vehicle::Type vehicleType;

    std::vector<Vehicle *> vehicles;
    std::vector<Animal *> animals;
    TrafficLight *trafficlight;

    void updateCurrent(sf::Time dt);
    void buildLane();

public:
    void saveLaneData(const std::string &filename) override;
    void loadLaneData(const std::string &filename) override;
};

#endif
