#ifndef LANE_HPP
#define LANE_HPP

#include <ViewGroup.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SeqZone.hpp>

class SeqZone;

class Lane: public Entity {
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
    virtual bool receivePlayer(ViewGroup* player);
    virtual bool spawnPlayer(ViewGroup::Ptr player);
    virtual unsigned int getCategory() const;

protected:
    TextureManager* laneTextures;
    sf::Sprite sprite;
    bool isReverse;
    Type type;
    SeqZone* seqZone;

private:
    virtual void updateCurrent(sf::Time dt) = 0;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void buildLane() = 0;
};

#endif