#ifndef GREEN_HPP
#define GREEN_HPP
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Green : public Entity
{
public:
    enum Type
    {
        Tree,
        Bush,
        CircleBush,
        Count
    };

    Green(Type mType, const TextureManager &textures);
    unsigned int getCategory() const;
    // dummy overide methods to prevent tree from moving
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);

private:
    Type type;

public:
    struct GreenData {
        int type;
        float x;
        float y;
    };

    GreenData serialize() const;
    void deserialize(GreenData& data);
};

#endif
