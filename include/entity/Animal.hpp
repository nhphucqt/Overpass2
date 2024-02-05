#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <Animation.hpp>
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Animal : public Entity
{
public:
    typedef std::unique_ptr<Animal> Ptr;

    enum class Type
    {
        Bear,
        Boar,
        Bunny,
        Deer,
        Fox,
        Wolf,
        Count
    };

    Animal(Type mType, const TextureHolder &textures);
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    unsigned int getCategory() const;

    void reverseSprite() override;

private:
    Type type;
    Animation animation;

protected:
    virtual void updateCurrent(sf::Time dt) override;

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

private:
    TextureID toTextureID(Type type);
};

#endif
