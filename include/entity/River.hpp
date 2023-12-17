#ifndef RIVER_HPP
#define RIVER_HPP
#include <Log.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class River: public Lane {
public:
    River(TextureManager* textures, bool isReverse = false);

private:
	std::vector<Log *> logs;
    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif