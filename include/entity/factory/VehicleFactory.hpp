#ifndef VEHICLE_FACTORY_HPP
#define VEHICLE_FACTORY_HPP

#include <Vehicle.hpp>
#include <ResourceID.hpp>

class VehicleFactory {
public:
    typedef std::unique_ptr<VehicleFactory> Ptr;

private:
    TextureManager* textures;
    static const int NUM_LEN = 2;
    static const int LOG_LEN[NUM_LEN];
    bool isReverse;
    float velocity;
    float roadLength;
    int __nextType;

public:
    VehicleFactory(TextureManager* textures, bool isReverse, float velocity, float riverLength);
    Vehicle::Ptr createVehicle();

private:
    void nextType();
    Vehicle::Type getNextType();
};

#endif