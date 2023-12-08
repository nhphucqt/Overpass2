#ifndef RIVER_HPP
#define RIVER_HPP
#include <ViewGroup.hpp>
#include <Log.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class River: public ViewGroup {
public:
    River(TextureManager* textures);

private:
    sf::Sprite sprite;
    TextureManager* riverTexture;
	std::vector<Log *> logs;

    void updateCurrent(sf::Time dt);
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void loadTextures();
    void buildRiver();
};

#endif