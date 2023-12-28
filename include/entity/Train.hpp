#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Train : public Entity
{
public:
    Train(const TextureManager &textures);
    unsigned int getCategory() const;

public:
    struct TrainData {
        float trainPosX;
        float trainPosY;
    };

public:
    struct TrainData {
        float posX;
        float posY;
        float vx;
        float vy;
        float scaleX;
        float scaleY;
    };

    TrainData serialize() const;
    void deserialize(TrainData& data);
};

#endif
