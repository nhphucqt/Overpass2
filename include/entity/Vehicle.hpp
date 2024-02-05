#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Vehicle : public Entity
{
public:
    typedef std::unique_ptr<Vehicle> Ptr;

    enum class Type
    {
        Car,
        Taxi,
        Police,
        Ambulance,
        Supercar,
        Count
    };

    Vehicle(Type mType, const TextureHolder &textures);
    unsigned int getCategory() const;

private:
    Type type;

public:
    struct VehicleData {
        int type;
        float posX;
        float posY;
        float vx;
        float vy;
        float scaleX;
        float scaleY;
        bool isReverse;
    };
    
    VehicleData serialize() const;
    void deserialize(VehicleData& data);

private:
    TextureID toTextureID(Type type);
};

#endif
