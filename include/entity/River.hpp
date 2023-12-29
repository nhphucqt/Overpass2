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
    unsigned int getCategory() const;

private:
    static constexpr float laneLength = 1400.f;
    static constexpr float padding = 100.f;
    static const int numOfLog = 3;
    static constexpr float logVelocity = 200.f;
	std::vector<Log *> logs;
    void updateCurrent(sf::Time dt);
    void buildLane();

    void pushLogZones(Log* log);
    void removeLogZones(Log* log);
};

#endif