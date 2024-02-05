#ifndef LANE_HPP
#define LANE_HPP

#include <ViewGroup.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SeqZone.hpp>

class SeqZone;

class Lane: public Entity {
public:
    enum class Type {
        Road = 0,
        Field,
        River,
        Railway,
        Count
    };
    
    Lane(const sf::Texture &texture, TextureHolder* textures, bool reverse = false);
	virtual sf::FloatRect getBoundingRect() const;
    virtual bool receivePlayer(ViewGroup* player);
    virtual bool spawnPlayer(ViewGroup::Ptr player, int index);
    virtual bool spawnPlayer(ViewGroup::Ptr player);
    virtual float getNearestDistance(ViewGroup* player) const;
    virtual Zone* getTargetZone(ViewGroup* player, const sf::Vector2f& dest, float dt) const;
    virtual unsigned int getCategory() const;

protected:
    TextureHolder* laneTextures;
    sf::Sprite sprite;
    bool isReverse;
    Type type;
    SeqZone* seqZone;

private:
    virtual void updateCurrent(sf::Time dt) = 0;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void buildLane() = 0;

protected:
    virtual bool isOutofView(Entity* entity, float laneLength) const;
    virtual bool isIntoView(Entity* entity, float laneLength) const;

public:
    Type getType() const { return type; }
    bool getIsReverse() const { return isReverse; }
    virtual void saveLaneData(std::ofstream& outf) = 0;
    virtual void loadLaneData(std::ifstream& inf) = 0;
};

#endif