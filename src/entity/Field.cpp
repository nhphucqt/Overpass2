#include "SFML/System/Vector2.hpp"

#include <AppConfig.hpp>
#include <Field.hpp>
#include <RectangleView.hpp>
#include <MyRandom.hpp>

Field::Field(TextureManager *textures, bool isReverse, const Greens& greenSlots, bool isLoad) 
    : Lane(textures->get(TextureID::Field), textures, isReverse), greenSlots(greenSlots)
{
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    float laneLength = cellSize.x * greenSlots.size();
    setSize(sf::Vector2f(laneLength, cellSize.y));
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

Field::Field(TextureManager *textures, bool isReverse, bool isLoad)
    : Field(textures, isReverse, {}, isLoad) {}

// buildLane is for initialization (it is called in constructor)
// add is for later processes
void Field::add(std::unique_ptr<Green> green, unsigned int index)
{
    green->setOrigin(Field::calcGreenCenter(*green));
    green->setPosition(Field::calcGreenPosition(*green, index));
    greens.push_back(green.get());
    this->attachView(std::move(green));
}

bool Field::spawnPlayer(ViewGroup::Ptr player)
{
    std::vector<bool> markSlots(seqZone->getNumZone(), false);
    for (const auto& slot : greenSlots) {
        markSlots[slot.first] = true;
    }
    std::vector<int> emptySlots;
    for (int i = 0; i < markSlots.size(); i++) {
        if (!markSlots[i]) {
            emptySlots.push_back(i);
        }
    }
    int index = MyRandom::sample(1, emptySlots)[0];
    return seqZone->spawnPlayer(std::move(player), index);
}

void Field::updateCurrent(sf::Time dt)
{
    // currently update nothing because bushes don't move
}

void Field::buildLane() {
    for (auto const &[index, green_type] : greenSlots) {
        auto green = std::make_unique<Green>(green_type, *laneTextures);
        add(std::move(green), index);
    }
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
        
        int numGreen = greenSlots.size();
        outf.write(reinterpret_cast<const char *>(&numGreen), sizeof(numGreen));

        for (const auto &green : greenSlots) {
            int index = green.first;
            int greenType = static_cast<int>(green.second);
            outf.write(reinterpret_cast<const char *>(&index), sizeof(index));
            outf.write(reinterpret_cast<const char *>(&greenType), sizeof(greenType));
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
        int numGreen;
        inf.read(reinterpret_cast<char *>(&numGreen), sizeof(numGreen));
        for (int i = 0; i < numGreen; i++) {
            int index;
            int greenType;
            inf.read(reinterpret_cast<char *>(&index), sizeof(index));
            inf.read(reinterpret_cast<char *>(&greenType), sizeof(greenType));
            greenSlots.emplace_back(index, static_cast<Green::Type>(greenType));
        }
        buildLane();
    }
    else
    {
        std::runtime_error("FIELDDATA ERR: \"save.data\" not found.\n");
    }
}
