#ifndef ROAD_HPP
#define ROAD_HPP

#include <Animal.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace DEFAULT {
    float LANELENGTH = 1400.f;
    float PADDING = 100.f;
    const int NUMOFVEHICLE = 3;
    const int NUMOFANIMAL = 2;
    float VEHICLEVELOCITY = 300.f;
    float VEHICLESLOWVELOCITY = 100.f;
    float ANIMALVELOCITY = 200.f;
    float TRAFFICLIGHTPOSITION = 400.f;
};

class Road : public Lane
{
public:
    Road(TextureManager* textures, bool isReverse = false);
    unsigned int getCategory() const;
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

    std::vector<Vehicle *> vehicles;
    std::vector<Animal *> animals;
    TrafficLight *trafficlight;

    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif
