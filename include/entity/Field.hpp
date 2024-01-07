#ifndef FIELD_HPP
#define FIELD_HPP

#include "SFML/System/Vector2.hpp"

#include <FieldProperties.hpp>
#include <Green.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <fstream>
#include <iostream>

class Field : public Lane
{
public:
    typedef std::vector<std::pair<unsigned int, Green::Type>> Greens;

public:
    Field(TextureManager *textures, bool isReverse, const Greens &greenSlots,
          bool isLoad = false);
    Field(TextureManager *textures, bool isReverse, bool isLoad = false);

    void add(std::unique_ptr<Green> green, unsigned int index);

    bool spawnPlayer(ViewGroup::Ptr player) override;

private:
    static sf::Vector2f calcGreenCenter(Green const &green);
    static sf::Vector2f calcGreenPosition(Green const &green,
                                          unsigned int index);

    Greens greenSlots;
    std::vector<Green *> greens;
    void updateCurrent(sf::Time dt);
    void buildLane();

public:
    void saveLaneData(std::ofstream &outf) override;
    void loadLaneData(std::ifstream &inf) override;
};

#endif
