#include "Animal.hpp"

#include <AppConfig.hpp>
#include <Road.hpp>

namespace DEFAULT
{
    const float LANELENGTH = 1400.f;
    const float PADDING = 100.f;
    const int NUMOFVEHICLE = 3;
    const int NUMOFANIMAL = 2;
    const float VEHICLEVELOCITY = 300.f;
    const float VEHICLESLOWVELOCITY = 100.f;
    const float ANIMALVELOCITY = 200.f;
    const float TRAFFICLIGHTPOSITION = 400.f;
}; // namespace DEFAULT

Road::Road(TextureManager *textures, bool isReverse, unsigned int vehicles_cnt,
           unsigned int animals_cnt, Vehicle::Type vehicle_type,
           Animal::Type animal_type, float velocity)
    : Lane(textures->get(TextureID::Road), textures, isReverse),
      laneLength(DEFAULT::LANELENGTH),
      padding(DEFAULT::PADDING),
      numOfVehicle(vehicles_cnt),
      numOfAnimal(animals_cnt),
      vehicleVelocity(velocity),
      vehicleSlowVelocity(DEFAULT::VEHICLESLOWVELOCITY),
      animalVelocity(velocity),
      trafficLightPosition(DEFAULT::TRAFFICLIGHTPOSITION),
      animalType(animal_type),
      vehicleType(vehicle_type)
{
    type = Lane::Road;
    textures->get(TextureID::Road).setRepeated(true);
    sprite.scale(8.f, 8.f);
    sf::IntRect textureRect(0, 0, laneLength, 16);
    sprite.setTextureRect(textureRect);
    if (!isLoad)
    {
        buildLane();
    }
}

void Road::setNumOfVehicle(int n)
{
    numOfVehicle = n;
}

void Road::setNumOfAnimal(int n)
{
    numOfAnimal = n;
}

void Road::setVehicleVelocity(float v)
{
    vehicleVelocity = v;
}

void Road::setVehicleSlowVelocity(float v)
{
    vehicleSlowVelocity = v;
}

void Road::setAnimalVelocity(float v)
{
    animalVelocity = v;
}

void Road::setTrafficLightPosition(float position)
{
    trafficLightPosition = position;
}

void Road::updateCurrent(sf::Time dt)
{
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // vehicles responding to traffic light
    TrafficLight::Color curColor = trafficlight->getCurrentColor();
    if (curColor == TrafficLight::Color::Red)
        for (auto &x : vehicles)
            x->setVelocity(0, 0);
    else if (curColor == TrafficLight::Color::Green)
        for (auto &x : vehicles)
            x->setVelocity(vehicleVelocity * reverseScale, 0.f);
    else
        for (auto &x : vehicles)
            x->setVelocity(vehicleSlowVelocity * reverseScale, 0.f);
    std::cout << "road is fine1\n";

    // vehicle circling when out of view
    Vehicle *lastVehicle = vehicles.back();
    Vehicle *firstVehicle = vehicles.front();
    int distanceVehicle = laneLength / vehicles.size();
    if ((isReverse && lastVehicle->getPosition().x < -padding) || (!isReverse && lastVehicle->getPosition().x > laneLength + padding))
    {
        vehicles[vehicles.size() - 1]->setPosition(
            firstVehicle->getPosition().x - padding * reverseScale - distanceVehicle * reverseScale,
            lastVehicle->getPosition().y);
    }
    // make the last car becomes the first car in the next iteration
    // vehicles.erase(vehicles.end());
    std::rotate(vehicles.rbegin(), vehicles.rbegin() + 1, vehicles.rend());

    Animal *lastAnimal = animals.back();
    Animal *firstAnimal = animals.front();
    int distanceAnimal = laneLength / animals.size();
    if ((isReverse && lastAnimal->getPosition().x < -padding) || (!isReverse && lastAnimal->getPosition().x > laneLength + padding))
    {
        animals[animals.size() - 1]->setPosition(
            firstAnimal->getPosition().x - padding * reverseScale - distanceAnimal * reverseScale,
            lastAnimal->getPosition().y);
    }
    // make the last animal becomes the first animal in the next iteration
    // animals.erase(animals.end());
    std::rotate(animals.rbegin(), animals.rbegin() + 1, animals.rend());
}

void Road::buildLane()
{
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // creating vehicles, vehicles should have the same type for consisteny
    for (int i = 0; i < numOfVehicle; ++i)
    {
        std::unique_ptr<Vehicle> vehicle(
            new Vehicle(vehicleType, *laneTextures));
        vehicles.push_back(vehicle.get());
        // vehicle->setPosition((laneLength + padding) / numOfVehicle *
        // i, 64.f);
        vehicle->setVelocity(vehicleVelocity * reverseScale, 0.f);
        vehicle->scale(reverseScale, 1);
        this->attachView(std::move(vehicle));
    }

    // create animals, animals should have the same type for consistency
    for (int i = 0; i < numOfAnimal; ++i)
    {
        std::unique_ptr<Animal> bear(new Animal(animalType, *laneTextures));
        animals.push_back(bear.get());
        bear->setPosition((laneLength + padding) / numOfAnimal * i, 16.f);
        bear->setVelocity(animalVelocity * reverseScale, 0.f);
        bear->scale(reverseScale, 1);
        this->attachView(std::move(bear));
    }

    // reverse vehicle and animal vectors for updateCurrent
    if (isReverse)
    {
        std::reverse(vehicles.begin(), vehicles.end());
        std::reverse(animals.begin(), animals.end());
    }

    // create traffic light
    std::unique_ptr<TrafficLight> light(new TrafficLight(*laneTextures));
    light->setPosition(
        laneLength * isReverse + trafficLightPosition * reverseScale, 64.f);
    light->scale(reverseScale, 1);
    trafficlight = light.get();
    this->attachView(std::move(light));
}

void Road::saveLaneData(const std::string &filename)
{
    std::ofstream outf(filename, std::ios::binary);
    if (outf.is_open())
    {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        int vehicleDataSize = vehicles.size();
        int animalDataSize = animals.size();
        outf.write(reinterpret_cast<const char *>(&vehicleDataSize), sizeof(vehicleDataSize));
        outf.write(reinterpret_cast<const char *>(&animalDataSize), sizeof(animalDataSize));

        for (auto &vehicle : vehicles)
        {
            Vehicle::VehicleData data = vehicle->serialize();
            outf.write(reinterpret_cast<const char *>(&data), sizeof(data));
        }
        for (auto &animal : animals)
        {
            Animal::AnimalData data = animal->serialize();
            outf.write(reinterpret_cast<const char *>(&data), sizeof(data));
        }

        outf.close();
    }
    else
    {
        std::runtime_error("ROADDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void Road::loadLaneData(const std::string &filename)
{
    std::ifstream inf(filename, std::ios::binary);
    if (inf.is_open())
    {
        int nType;
        bool nIsReverse;
        inf.read(reinterpret_cast<char *>(&nType), sizeof(nType));
        inf.read(reinterpret_cast<char *>(&nIsReverse), sizeof(nIsReverse));

        int vehicleDataSize;
        int animalDataSize;
        inf.read(reinterpret_cast<char *>(&vehicleDataSize), sizeof(vehicleDataSize));
        inf.read(reinterpret_cast<char *>(&animalDataSize), sizeof(animalDataSize));

        std::cout << "vehicle size: " << vehicleDataSize << std::endl;
        std::cout << "animal size: " << animalDataSize << std::endl;

        int reverseScale = (nIsReverse) ? -1 : 1;

        for (int i = 0; i < vehicleDataSize; ++i)
        {
            Vehicle::VehicleData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Vehicle> vehiclePtr(new Vehicle(static_cast<Vehicle::Type>(data.type), *laneTextures));
            vehiclePtr->deserialize(data);
            vehicles.push_back(vehiclePtr.get());
            this->attachView(std::move(vehiclePtr));
        }
        for (int i = 0; i < animalDataSize; ++i)
        {
            Animal::AnimalData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Animal> animalPtr(new Animal(static_cast<Animal::Type>(data.type), *laneTextures));
            animalPtr->deserialize(data);
            animals.push_back(animalPtr.get());
            this->attachView(std::move(animalPtr));
        }

        std::unique_ptr<TrafficLight> light(new TrafficLight(*laneTextures));
        light->setPosition(laneLength * isReverse + trafficLightPosition * reverseScale, 64.f);
        light->scale(reverseScale, 1);
        trafficlight = light.get();
        this->attachView(std::move(light));
    }
    else
    {
        std::runtime_error("ROADDATA ERR: " + filename + " not found.\n");
    }
}