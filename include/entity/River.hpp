#ifndef RIVER_HPP
#define RIVER_HPP
#include <Log.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SeqZoneRiver.hpp>

class River: public Lane {
public:
    River(TextureManager* textures, bool isReverse = false);
    void setNumOfLog(int n);
    void setlogVelocity(float v);

private:
    float laneLength;
    float padding;
    int numOfLog;
    float logVelocity;
	std::vector<Log *> logs;
    void updateCurrent(sf::Time dt);
    void buildLane();

    void pushLogZones(Log* log);
    void removeLogZones(Log* log);
};

#endif