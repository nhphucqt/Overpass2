#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <Entity.hpp>
#include <ResourceManager.hpp>
#include <ResourceID.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Vehicle: public Entity {
public:
    enum Type {Car};
    Vehicle(Type mType, const TextureManager& textures);
    // virtual unsigned int getCategory() const;

private:
    Type type;
};

#endif