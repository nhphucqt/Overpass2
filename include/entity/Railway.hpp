#ifndef RAILWAY_HPP
#define RAILWAY_HPP
#include <Train.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Railway: public Lane {
public:
    Railway(TextureManager* textures, ViewGroup* foreground, bool isReverse = false);
    unsigned int getCategory() const;

private:
	Train* train;
    ViewGroup* foreground;
    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif