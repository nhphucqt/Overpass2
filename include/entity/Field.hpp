#ifndef FIELD_HPP
#define FIELD_HPP

#include "SFML/System/Vector2.hpp"

#include "SFML/System/Vector2.hpp"

#include <fstream>
#include <iostream>
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
    Field(TextureManager *textures, bool isReverse = false, bool isLoad = false, bool isLoad = false);
    void add(std::unique_ptr<Green> green, unsigned int index);

private:
    static sf::Vector2f calcGreenCenter(Green const &green);
    static sf::Vector2f calcGreenPosition(Green const &green,
                                          unsigned int index);

    std::vector<Green *> greens;
    void updateCurrent(sf::Time dt);
    void buildLane();

public:
    void saveLaneData(std::ofstream &outf) override;
    void loadLaneData(std::ifstream &inf) override;
};

#endif
