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
        Road = 0,
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

public:
    Type getType() const { return type; }
    bool getIsReverse() const { return isReverse; }
    virtual void saveLaneData(const std::string& filename) = 0;
    virtual void loadLaneData(const std::string& filename) = 0;
};

#endif