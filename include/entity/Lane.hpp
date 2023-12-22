#ifndef LANE_HPP
#define LANE_HPP

#include <ViewGroup.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Lane: public ViewGroup {
public:
    enum Type {
        Road,
        Field,
        River,
        Railway,
        Count
    };
    
    Lane(const sf::Texture &texture, TextureManager* textures, bool reverse = false);
	virtual sf::FloatRect getBoundingRect() const;

protected:
    TextureManager* laneTextures;
    sf::Sprite sprite;
    bool isReverse;
    Type type;

private:
    virtual void updateCurrent(sf::Time dt) = 0;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void buildLane() = 0;
};

#endif