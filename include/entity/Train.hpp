#ifndef TRAIN_HPP
#define TRAIN_HPP
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Train: public Entity {
public:
    Train(const TextureManager& textures);
    unsigned int getCategory() const;
    sf::FloatRect getBoundingRect() const;

private:
};

#endif