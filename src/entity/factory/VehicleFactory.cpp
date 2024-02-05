#include <VehicleFactory.hpp>
#include <MyRandom.hpp>

const int VehicleFactory::LOG_LEN[NUM_LEN] = {2, 3};

VehicleFactory::VehicleFactory(TextureHolder* textures, bool isReverse, float velocity, float roadLength)
: textures(textures), isReverse(isReverse), velocity(velocity), roadLength(roadLength) {
    nextType();
}

Vehicle::Ptr VehicleFactory::createVehicle() {
    Vehicle::Ptr vehicle(new Vehicle(getNextType(), *textures));
    if (isReverse) {
        vehicle->reverseSprite();
        vehicle->setPosition(roadLength, 0.f);
        vehicle->setVelocity(-velocity, 0.f);
    } else {
        vehicle->setPosition(-vehicle->getSize().x, 0.f);
        vehicle->setVelocity(velocity, 0.f);
    }
    nextType();
    return std::move(vehicle);
}

void VehicleFactory::nextType() {
    __nextType = MyRandom::random_range((unsigned int)Vehicle::Type::Count);
}

Vehicle::Type VehicleFactory::getNextType() {
    return (Vehicle::Type)__nextType;
}