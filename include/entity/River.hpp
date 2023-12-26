#ifndef RIVER_HPP
#define RIVER_HPP

#include <iostream>
#include <fstream>
#include <Log.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class River: public Lane {
public:
    River(TextureManager* textures, bool isReverse = false, bool isLoad = false);
    unsigned int getCategory() const;

private:
	std::vector<Log *> logs;
    void updateCurrent(sf::Time dt);
    void buildLane();

    struct RiverData {
        std::vector<Log::LogData> logsData;  
    };
    
public:
    void saveLaneData(const std::string& filename) override;
    void loadLaneData(const std::string& filename) override;
};

#endif