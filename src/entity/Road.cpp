#include <Road.hpp>
#include <AppConfig.hpp>

namespace DEFAULT {
    const float LANELENGTH = 1400.f;
    const float PADDING = 100.f;
    const int NUMOFVEHICLE = 3;
    const int NUMOFANIMAL = 2;
    const float VEHICLEVELOCITY = 300.f;
    const float VEHICLESLOWVELOCITY = 100.f;
    const float ANIMALVELOCITY = 200.f;
    const float TRAFFICLIGHTPOSITION = 400.f;
};

Road::Road(TextureManager *textures, bool isReverse)
: Lane(textures->get(TextureID::Road), textures, isReverse)
, laneLength(DEFAULT::LANELENGTH)
, padding(DEFAULT::PADDING)
, numOfVehicle(DEFAULT::NUMOFVEHICLE)
, numOfAnimal(DEFAULT::NUMOFANIMAL)
, vehicleVelocity(DEFAULT::VEHICLEVELOCITY)
, vehicleSlowVelocity(DEFAULT::VEHICLESLOWVELOCITY)
, animalVelocity(DEFAULT::ANIMALVELOCITY)
, trafficLightPosition(DEFAULT::TRAFFICLIGHTPOSITION)
{
    type = Lane::Road;
    textures->get(TextureID::Road).setRepeated(true);
    sprite.scale(8.f, 8.f);
	sf::IntRect textureRect(0, 0, laneLength, 16);
    sprite.setTextureRect(textureRect);
    buildLane();   
}

void Road::setNumOfVehicle(int n) {
    numOfVehicle = n;
}

void Road::setNumOfAnimal(int n) {
    numOfAnimal = n;
}

void Road::setVehicleVelocity(float v) {
    vehicleVelocity = v;
}

void Road::setVehicleSlowVelocity(float v) {
    vehicleSlowVelocity = v;
}

void Road::setAnimalVelocity(float v) {
    animalVelocity = v;
}

void Road::setTrafficLightPosition(float position) {
    trafficLightPosition = position;
}

void Road::updateCurrent(sf::Time dt) {
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // vehicles responding to traffic light
    TrafficLight::Color curColor = trafficlight->getCurrentColor();
    if(curColor == TrafficLight::Color::Red)
        for(auto& x : vehicles)
            x->setVelocity(0, 0);
    else if (curColor == TrafficLight::Color::Green)
        for(auto& x : vehicles)
            x->setVelocity(vehicleVelocity * reverseScale, 0.f);
    else
        for(auto& x : vehicles)
            x->setVelocity(vehicleSlowVelocity * reverseScale, 0.f);

    // vehicle circling when out of view
    Vehicle* lastVehicle = vehicles.back();
    Vehicle* firstVehicle = vehicles.front();
    int distanceVehicle = laneLength/vehicles.size();
    if ((isReverse && lastVehicle->getPosition().x < -padding) || (!isReverse && lastVehicle->getPosition().x > laneLength + padding))
        vehicles[vehicles.size() - 1]->setPosition(firstVehicle->getPosition().x - padding * reverseScale - distanceVehicle * reverseScale, lastVehicle->getPosition().y);
    // make the last car becomes the first car in the next iteration
    vehicles.pop_back();
    vehicles.insert(vehicles.begin(), lastVehicle);

    Animal* lastAnimal = animals.back();
    Animal* firstAnimal = animals.front();
    int distanceAnimal = laneLength/animals.size();
    if ((isReverse && lastAnimal->getPosition().x < -padding) || (!isReverse && lastAnimal->getPosition().x > laneLength + padding))
        animals[animals.size() - 1]->setPosition(firstAnimal->getPosition().x - padding * reverseScale - distanceAnimal * reverseScale, lastAnimal->getPosition().y);
    // make the last animal becomes the first animal in the next iteration
    // animals.erase(animals.end());
    animals.pop_back();
    animals.insert(animals.begin(), lastAnimal);
}

void Road::buildLane() {
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // creating vehicles, vehicles should have the same type for consisteny
    for (int i = 0; i < numOfVehicle; ++i) {
        std::unique_ptr<Vehicle> vehicle(new Vehicle(Vehicle::Car, *laneTextures));
        vehicles.push_back(vehicle.get());
        // vehicle->setPosition((laneLength + padding) / numOfVehicle * i, 64.f);
        vehicle->setVelocity(vehicleVelocity * reverseScale, 0.f);
        vehicle->scale(reverseScale, 1);
        this->attachView(std::move(vehicle));
    }

    // create animals, animals should have the same type for consistency
    for (int i = 0; i < numOfAnimal; ++i) {
        std::unique_ptr<Animal> bear(new Animal(Animal::Fox, *laneTextures));
        animals.push_back(bear.get());
        bear->setPosition((laneLength + padding) / numOfAnimal * i, 16.f);
        bear->setVelocity(animalVelocity * reverseScale, 0.f);
        bear->scale(reverseScale, 1);
        this->attachView(std::move(bear));
    }

    // reverse vehicle and animal vectors for updateCurrent
    if (isReverse) {
        std::reverse(vehicles.begin(), vehicles.end());
        std::reverse(animals.begin(), animals.end());
    }

    // create traffic light
    std::unique_ptr<TrafficLight> light(new TrafficLight(*laneTextures));
    light->setPosition(laneLength * isReverse + trafficLightPosition * reverseScale, 64.f);
    light->scale(reverseScale, 1);
    trafficlight = light.get();
    this->attachView(std::move(light));
}