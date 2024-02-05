#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Train : public Entity
{
public:
    typedef std::unique_ptr<Train> Ptr;

    Train(const TextureHolder &textures);
    unsigned int getCategory() const;

public:
    struct TrainData
    {
        float posX;
        float posY;
        float vx;
        float vy;
        float scaleX;
        float scaleY;
        bool isReversed;
    };

    TrainData serialize() const;
    void deserialize(TrainData &data);

    void reverseSprite() override;
};

#endif
