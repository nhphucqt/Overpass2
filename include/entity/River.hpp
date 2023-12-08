#ifndef RIVER_HPP
#define RIVER_HPP
#include <ResourceManager.hpp>
#include <ResourceID.hpp>
#include <ViewGroup.hpp>
#include <TrafficLight.hpp>
#include <Animal.hpp>
#include <Vehicle.hpp>
#include <Log.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class River: public ViewGroup {
public:
    River(const TextureManager* textures);

private:
    sf::Sprite sprite;
    TextureManager riverTexture;
	std::vector<Log *> logs;

    void updateCurrent(sf::Time dt);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadTextures();
    void buildRiver();
};

#endif