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
    typedef std::unique_ptr<Train> Ptr;

    Train(const TextureManager &textures);
    unsigned int getCategory() const;

    void reverseSprite() override;

private:
};

#endif
