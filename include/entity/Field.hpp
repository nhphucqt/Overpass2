#ifndef FIELD_HPP
#define FIELD_HPP

#include <Green.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Field: public Lane {
public:
    Field(TextureManager* textures, bool isReverse = false);

private:
    std::vector<Green *> greens;
    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif