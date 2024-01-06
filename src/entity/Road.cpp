#include "Animal.hpp"

#include <AppConfig.hpp>
#include <Road.hpp>

const float Road::VEHICLE_SLOW_VELOCITY = 100.f;
const float Road::TRAFFIC_LIGHT_POSITION = 400.f;
const float Road::ANIMAL_TIMER_LOW = 3.f;
const float Road::ANIMAL_TIMER_HIG = 5.f;
const float Road::VEHICLE_TIMER_LOW = 1.f;
const float Road::VEHICLE_TIMER_HIG = 2.f;

Road::Road(TextureManager *textures, bool isReverse, float animalVelo, float vehicleVelo, bool hasAnimal, bool hasVehicle)
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
    setReverse(true);
    type = Lane::Road;
    textures->get(TextureID::Road).setRepeated(true);
    sprite.scale(8.f, 8.f);
    sf::IntRect textureRect(0, 0, laneLength, 16);
    sprite.setTextureRect(textureRect);
    buildLane();
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
    float reverseScale = (isReverse) ? -1 : 1;
    // create traffic light
    std::unique_ptr<TrafficLight> light(new TrafficLight(*laneTextures));
    light->setPosition(laneLength * isReverse + trafficLightPosition * reverseScale, 0);
    // light->scale(reverseScale, 1);
    trafficlight = light.get();
    this->attachView(std::move(light));

    if (checkHasVehicle()) {
        createVehicle();
    }
    if (checkHasAnimal()) {
        createAnimal();
    }
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
    animals.push(animal.get());
    attachView(std::move(animal));
}

void Road::popAnimal() {
    detachView(*animals.front());
    animals.pop();
}

bool Road::checkHasVehicle()
{
    return hasVehicle;
}

bool Road::checkHasAnimal()
{
    return hasAnimal;
}

