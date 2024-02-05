#ifndef ROAD_HPP
#define ROAD_HPP

#include <fstream>
#include <iostream>
#include <Lane.hpp>
#include <TrafficLight.hpp>
#include <Animal.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <TrafficLight.hpp>
#include <Vehicle.hpp>

#include <MyTimer.hpp>
#include <AnimalFactory.hpp>
#include <VehicleFactory.hpp>

class Road : public Lane
{
public:
    static const float VEHICLE_SLOW_VELOCITY;
    static const float TRAFFIC_LIGHT_POSITION;
    static const float ANIMAL_TIMER_LOW;
    static const float ANIMAL_TIMER_HIG;
    static const float VEHICLE_TIMER_LOW;
    static const float VEHICLE_TIMER_HIG;

    Road(TextureHolder *textures, bool isReverse, float animalVelo, float vehicleVelo, bool hasAnimal, bool hasVehicle, bool isLoad = false);

    void setVehicleVelocity(float v);
    void setVehicleSlowVelocity(float v);
    void setAnimalVelocity(float v);
    void setTrafficLightPosition(float position);

private:
    float laneLength;
    float vehicleVelocity;
    float vehicleSlowVelocity;
    float animalVelocity;
    float trafficLightPosition;

    bool hasVehicle;
    bool hasAnimal;

    std::list<Vehicle*> vehicles;
    std::list<Animal*> animals;

    VehicleFactory::Ptr vehicleFactory;
    AnimalFactory::Ptr animalFactory;

    MyTimer vehicleTimer;
    MyTimer animalTimer;

    TrafficLight* trafficlight;

    void updateCurrent(sf::Time dt);
    void updateTraffic(sf::Time dt);
    void buildLane();

    void buildTrafficLight();

    void updateVehicle(sf::Time dt);
    void updateAnimal(sf::Time dt);

    void createVehicle();
    void popVehicle();
    void createAnimal();
    void popAnimal();

    bool checkHasVehicle();
    bool checkHasAnimal();

public:
    void saveLaneData(std::ofstream &outf) override;
    void loadLaneData(std::ifstream &inf) override;
};

#endif
