#ifndef RAILWAY_HPP
#define RAILWAY_HPP
#include <Train.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace DEFAULT {
    float LANELENGTH = 1400.f;
    float PADDING = 1000.f;
    float TRAINVELOCITY = 700.f;
};

class Railway: public Lane {
public:
    Railway(TextureManager* textures, ViewGroup* foreground, bool isReverse = false);
    unsigned int getCategory() const;
    void setTrainVelocity(float v);

private:
    float laneLength;
    float padding;
    float trainVelocity;
	Train* train;
    ViewGroup* foreground;
    void updateCurrent(sf::Time dt);
    void buildLane();
};

#endif