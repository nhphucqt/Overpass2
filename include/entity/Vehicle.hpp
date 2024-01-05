#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Vehicle : public Entity
{
public:
    typedef std::unique_ptr<Vehicle> Ptr;

    enum Type
    {
        Car,
        Taxi,
        Police,
        Ambulance,
        Count
    };

    Vehicle(Type mType, const TextureManager &textures);
    unsigned int getCategory() const;

private:
    Type type;
};

#endif
