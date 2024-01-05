#include "SFML/System/Vector2.hpp"

#include <AppConfig.hpp>
#include <Field.hpp>
#include <RectangleView.hpp>

Field::Field(TextureManager *textures, bool isReverse, bool isLoad) 
    : Lane(textures->get(TextureID::Field), textures, isReverse)
{
    type = Lane::Type::Field;
    textures->get(TextureID::Field).setRepeated(true);
    sprite.scale(4.f, 4.f);
    sf::IntRect textureRect(0, 0, 1400, 32);
    sprite.setTextureRect(textureRect);
    if (!isLoad)
    {
        buildLane();
    }
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

void Field::saveLaneData(std::ofstream &outf)
{
    if (outf.is_open())
    {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        int dataSize = greens.size();
        outf.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));

        for (const auto &green : greens)
        {
            Green::GreenData greendata = green->serialize();
            outf.write(reinterpret_cast<const char *>(&greendata), sizeof(greendata));
        }
    }
    else
    {
        std::runtime_error("FIELDDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void Field::loadLaneData(std::ifstream &inf)
{
    if (inf.is_open())
    {
        // int nType;
        // bool nIsReverse;
        // inf.read(reinterpret_cast<char*>(&nType), sizeof(nType));
        // inf.read(reinterpret_cast<char*>(&nIsReverse), sizeof(nIsReverse));

        int dataSize;
        inf.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
        std::cout << "total greens: " << dataSize << std::endl;

        for (int i = 0; i < dataSize; ++i)
        {
            Green::GreenData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Green> greenPtr(new Green(static_cast<Green::Type>(data.type), *laneTextures));
            greenPtr->deserialize(data);
            greens.push_back(greenPtr.get());
            this->attachView(std::move(greenPtr));
        }
        std::cout << "field is fine.\n";
    }
    else
    {
        std::runtime_error("FIELDDATA ERR: \"save.data\" not found.\n");
    }
}
