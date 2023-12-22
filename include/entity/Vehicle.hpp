#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Vehicle: public Entity {
public:
    enum Type {Car};
    Vehicle(Type mType, const TextureManager& textures);
    unsigned int getCategory() const;

private:
    Type type;
};

#endif