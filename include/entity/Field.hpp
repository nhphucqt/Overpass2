#ifndef FIELD_HPP
#define FIELD_HPP

#include "SFML/System/Vector2.hpp"

#include <Green.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Field : public Lane
{
public:
    Field(TextureManager *textures, bool isReverse = false);
    void add(std::unique_ptr<Green> green, unsigned int index);

    bool spawnPlayer(ViewGroup::Ptr player) override;

private:
    static sf::Vector2f calcGreenCenter(Green const &green);
    static sf::Vector2f calcGreenPosition(Green const &green,
                                          unsigned int index);

    std::vector<int> greenSlots;
    std::vector<Green *> greens;
    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif
