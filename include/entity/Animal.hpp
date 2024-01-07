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
    typedef std::unique_ptr<Animal> Ptr;

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

    void reverseSprite() override;

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
        bool isReverse;
    };
    
    AnimalData serialize() const;
    void deserialize(AnimalData& data);
};

#endif
