#ifndef RIVER_HPP
#define RIVER_HPP

#include <iostream>
#include <fstream>
#include <Log.hpp>
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
    static const float OUT_OF_VIEW_PADDING;


    River(TextureManager *textures, bool isReverse, float velocity, bool isLoad = false);
    void setLogVelocity(float v);

	virtual unsigned int getCategory() const;

private:
    float laneLength;
    float logVelocity;
    
    LogFactory::Ptr logFactory;
    std::list<Log*> logs;
    MyTimer timer;

    void updateCurrent(sf::Time dt);
    void buildLane();
    void buildZone();

    void createLog();
    void popLog();

    void pushLogZones(Log *log);
    void removeLogZones(Log *log);

public:
    void saveLaneData(std::ofstream &outf) override;
    void loadLaneData(std::ifstream &inf) override;

protected:
    virtual bool isOutofView(Entity* entity, float laneLength) const override;
};

#endif
