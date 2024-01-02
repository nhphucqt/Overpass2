#include "SFML/System/Vector2.hpp"

#include <AppConfig.hpp>
#include <Field.hpp>
#include <RectangleView.hpp>

Field::Field(TextureManager *textures, bool isReverse)
    : Lane(textures->get(TextureID::Field), textures, isReverse)
{
    type = Lane::Type::Field;
    textures->get(TextureID::Field).setRepeated(true);
    sprite.scale(4.f, 4.f);
    sf::IntRect textureRect(0, 0, 1400, 32);
    sprite.setTextureRect(textureRect);
    buildLane();
}

// buildLane is for initialization (it is called in constructor)
// add is for later processes
void Field::add(std::unique_ptr<Green> green, unsigned int index)
{
    green->setOrigin(Field::calcGreenCenter(*green));
    green->setPosition(Field::calcGreenPosition(*green, index));
    greens.push_back(green.get());
    this->attachView(std::move(green));
}

void Field::updateCurrent(sf::Time dt)
{
    // currently update nothing because bushes don't move
}

void Field::buildLane()
{
    // std::unique_ptr<Green> tree(new Green(Green::Tree, *laneTextures));
    // std::unique_ptr<Green> bush(new Green(Green::Bush, *laneTextures));
    // std::unique_ptr<Green> circleBush(new Green(Green::CircleBush,
    // *laneTextures)); greens.push_back(tree.get());
    // greens.push_back(bush.get());
    // greens.push_back(circleBush.get());
    // tree->setPosition(200, 96);
    // bush->setPosition(700, 64);
    // circleBush->setPosition(1200, 64);
    // this->attachView(std::move(tree));
    // this->attachView(std::move(bush));
    // this->attachView(std::move(circleBush));
}

sf::Vector2f Field::calcGreenCenter(Green const &green)
{
    return green.getLocalBounds().getSize() / 2.f;
}

sf::Vector2f Field::calcGreenPosition(Green const &green, unsigned int index)
{
    float const CELL_SIZE =
        AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).x;
    return {CELL_SIZE * index + CELL_SIZE / 2, CELL_SIZE / 2};
}
