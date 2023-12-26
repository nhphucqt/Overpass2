#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <Animation.hpp>
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Animal : public Entity
{
public:
    enum Type
    {
        Bear,
        Boar,
        Bunny,
        Deer,
        Fox,
        Wolf,
        Count
    };

    Animal(Type mType, const TextureManager &textures);
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    unsigned int getCategory() const;

private:
    Type type;
    Animation animation;
    void updateCurrent(sf::Time dt);

public:
    struct AnimalData {
        int type;
        float posX;
        float posY;
        float vx;
        float vy;
        float scaleX;
        float scaleY;
    };
    
    AnimalData serialize() const;
    void deserialize(AnimalData& data);
};

#endif
