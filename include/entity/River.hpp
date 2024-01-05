#ifndef RIVER_HPP
#define RIVER_HPP

#include <Lane.hpp>
#include <Log.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SeqZoneRiver.hpp>
#include <LogFactory.hpp>
#include <MyTimer.hpp>

class River : public Lane
{
public:
    static const float LOG_TIMER_LOW;
    static const float LOG_TIMER_HIG;


    River(TextureManager *textures, bool isReverse, float velocity);
    void setLogVelocity(float v);

private:
    float laneLength;
    float logVelocity;
    
    LogFactory::Ptr logFactory;
    std::queue<Log*> logs;
    MyTimer timer;

    void updateCurrent(sf::Time dt);
    void buildLane();
    void buildZone();

    void createLog();
    void popLog();
    bool isLogOutOfView(Log *log);
    bool isLogIntoView(Log *log);

    void pushLogZones(Log *log);
    void removeLogZones(Log *log);
};

#endif
