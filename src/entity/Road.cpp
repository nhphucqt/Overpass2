#include "Animal.hpp"

#include <AppConfig.hpp>
#include <Road.hpp>

const float Road::VEHICLE_SLOW_VELOCITY = 100.f;
const float Road::TRAFFIC_LIGHT_POSITION = 400.f;
const float Road::ANIMAL_TIMER_LOW = 3.f;
const float Road::ANIMAL_TIMER_HIG = 5.f;
const float Road::VEHICLE_TIMER_LOW = 1.f;
const float Road::VEHICLE_TIMER_HIG = 2.f;

Road::Road(TextureManager *textures, bool isReverse, float animalVelo, float vehicleVelo, bool hasAnimal, bool hasVehicle, bool isLoad)
    : Lane(textures->get(TextureID::Road), textures, isReverse),
      laneLength(AppConfig::getInstance().get<float>(ConfigKey::LANE_LENGTH)),
      vehicleVelocity(vehicleVelo),
      vehicleSlowVelocity(VEHICLE_SLOW_VELOCITY),
      animalVelocity(animalVelo),
      trafficLightPosition(TRAFFIC_LIGHT_POSITION),
      vehicleFactory(new VehicleFactory(textures, isReverse, vehicleVelocity, laneLength)),
      animalFactory(new AnimalFactory(textures, isReverse, animalVelocity, laneLength)),
      vehicleTimer(VEHICLE_TIMER_LOW, VEHICLE_TIMER_HIG),
      animalTimer(ANIMAL_TIMER_LOW, ANIMAL_TIMER_HIG),
      hasAnimal(hasAnimal),
      hasVehicle(hasVehicle)
{
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(sf::Vector2f(laneLength, cellSize.y));
    setReverse(true);
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
    updateTraffic(dt);
    if (checkHasVehicle() && trafficlight->isGreen()) {
        updateVehicle(dt);
    }
    if (checkHasAnimal()) {
        updateAnimal(dt);
    }
}

void Road::updateTraffic(sf::Time dt) {
    // vehicles responding to traffic light
    float reverseScale = (isReverse) ? -1 : 1;
    if (trafficlight->isRed()) {
        for (auto &x : vehicles) {
            x->setVelocity(0, 0);
        }
    } else if (trafficlight->isGreen()) {
        for (auto &x : vehicles) {
            x->setVelocity(vehicleVelocity * reverseScale, 0.f);
        }
    } else {
        for (auto &x : vehicles) {
            x->setVelocity(vehicleSlowVelocity * reverseScale, 0.f);
        }
    }
}

void Road::updateVehicle(sf::Time dt) {
    while (!vehicles.empty() && isOutofView(vehicles.front(), laneLength)) {
        popVehicle();
    }
    vehicleTimer.update(dt);
    if (!vehicleTimer.isTiming() && !vehicles.empty() && isIntoView(vehicles.back(), laneLength)) {
        vehicleTimer.restart();
    }
    if (vehicleTimer.isTimeout()) {
        vehicleTimer.stop();
        createVehicle();
    }
}

void Road::updateAnimal(sf::Time dt)
{
    while (!animals.empty() && isOutofView(animals.front(), laneLength)) {
        popAnimal();
    }
    animalTimer.update(dt);
    if (!animalTimer.isTiming() && !animals.empty() && isIntoView(animals.back(), laneLength)) {
        animalTimer.restart();
    }
    if (animalTimer.isTimeout()) {
        animalTimer.stop();
        createAnimal();
    }
}

void Road::buildLane()
{
    buildTrafficLight();

    if (checkHasVehicle()) {
        createVehicle();
    }
    if (checkHasAnimal()) {
        createAnimal();
    }
}

void Road::saveLaneData(std::ofstream &outf)
{
    if (outf.is_open())
    {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        outf.write(reinterpret_cast<const char *>(&animalVelocity), sizeof(animalVelocity));
        outf.write(reinterpret_cast<const char *>(&vehicleVelocity), sizeof(vehicleVelocity));
        outf.write(reinterpret_cast<const char *>(&hasAnimal), sizeof(hasAnimal));
        outf.write(reinterpret_cast<const char *>(&hasVehicle), sizeof(hasVehicle));

        int numOfVehicle = vehicles.size();
        int numOfAnimal = animals.size();
        outf.write(reinterpret_cast<const char *>(&numOfVehicle), sizeof(numOfVehicle));
        outf.write(reinterpret_cast<const char *>(&numOfAnimal), sizeof(numOfAnimal));

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

        MyTimer::MyTimerData vehicleTimerData = vehicleTimer.serialize();
        outf.write(reinterpret_cast<const char *>(&vehicleTimerData), sizeof(vehicleTimerData));

        MyTimer::MyTimerData animalTimerData = animalTimer.serialize();
        outf.write(reinterpret_cast<const char *>(&animalTimerData), sizeof(animalTimerData));

        TrafficLight::TrafficLightData trafficLightData = trafficlight->serialize();
        outf.write(reinterpret_cast<const char *>(&trafficLightData), sizeof(trafficLightData));
    }
    else
    {
        std::runtime_error("ROADDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void Road::loadLaneData(std::ifstream &inf) {
    if (inf.is_open()) {
        buildTrafficLight();

        int numOfVehicle, numOfAnimal;
        inf.read(reinterpret_cast<char *>(&numOfVehicle), sizeof(numOfVehicle));
        inf.read(reinterpret_cast<char *>(&numOfAnimal), sizeof(numOfAnimal));

        for (int i = 0; i < numOfVehicle; ++i)
        {
            Vehicle::VehicleData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Vehicle> vehiclePtr(new Vehicle(static_cast<Vehicle::Type>(data.type), *laneTextures));
            vehiclePtr->deserialize(data);
            vehicles.push_back(vehiclePtr.get());
            this->attachView(std::move(vehiclePtr));
        }
        for (int i = 0; i < numOfAnimal; ++i)
        {
            Animal::AnimalData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Animal> animalPtr(new Animal(static_cast<Animal::Type>(data.type), *laneTextures));
            animalPtr->deserialize(data);
            animals.push_back(animalPtr.get());
            this->attachView(std::move(animalPtr));
        }

        MyTimer::MyTimerData vehicleTimerData;
        inf.read(reinterpret_cast<char *>(&vehicleTimerData), sizeof(vehicleTimerData));
        vehicleTimer.deserialize(vehicleTimerData);

        MyTimer::MyTimerData animalTimerData;
        inf.read(reinterpret_cast<char *>(&animalTimerData), sizeof(animalTimerData));
        animalTimer.deserialize(animalTimerData);

        animalFactory.reset(new AnimalFactory(laneTextures, isReverse, animalVelocity, laneLength));
        vehicleFactory.reset(new VehicleFactory(laneTextures, isReverse, vehicleVelocity, laneLength));

        TrafficLight::TrafficLightData trafficLightData;
        inf.read(reinterpret_cast<char *>(&trafficLightData), sizeof(trafficLightData));
        trafficlight->deserialize(trafficLightData);
    }
    else
    {
        std::runtime_error("ROADDATA ERR: \"save.data\" not found.\n");
    }
}

void Road::buildTrafficLight() {
    float reverseScale = (isReverse) ? -1 : 1;
    std::unique_ptr<TrafficLight> light(new TrafficLight(*laneTextures));
    light->setPosition(laneLength * isReverse + trafficLightPosition * reverseScale, 0);
    trafficlight = light.get();
    this->attachView(std::move(light));
}

void Road::createVehicle()
{
    Vehicle::Ptr vehicle = vehicleFactory->createVehicle();
    vehicles.push_back(vehicle.get());
    attachView(std::move(vehicle));
}

void Road::popVehicle() {
    detachView(*vehicles.front());
    vehicles.pop_front();
}

void Road::createAnimal()
{
    Animal::Ptr animal = animalFactory->createAnimal();
    animals.push_back(animal.get());
    attachView(std::move(animal));
}

void Road::popAnimal() {
    detachView(*animals.front());
    animals.pop_front();
}

bool Road::checkHasVehicle()
{
    return hasVehicle;
}

bool Road::checkHasAnimal()
{
    return hasAnimal;
}

