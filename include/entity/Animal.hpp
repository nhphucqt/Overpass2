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
};

#endif
