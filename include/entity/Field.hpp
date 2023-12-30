#ifndef FIELD_HPP
#define FIELD_HPP

#include <fstream>
#include <iostream>
#include <Green.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Field: public Lane {
public:
    Field(TextureManager* textures, bool isReverse = false, bool isLoad = false);

private:
    std::vector<Green *> greens;
    void updateCurrent(sf::Time dt);
    void buildLane();
    
public:
    void saveLaneData(std::ofstream& outf) override;
    void loadLaneData(std::ifstream& inf) override;
};

#endif