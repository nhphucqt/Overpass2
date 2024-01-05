#ifndef RAILWAY_HPP
#define RAILWAY_HPP
#include <Train.hpp>
#include <Lane.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <TrainFactory.hpp>
#include <MyTimer.hpp>

#include <RailwayLight.hpp>

class Railway: public Lane {
public:
    static const float TRAIN_VELOCITY;

    Railway(TextureManager* textures, bool isReverse, float trainInterval, float trainDelay, float trainOffSet);
    void setTrainVelocity(float v);

private:
    float laneLength;
    float trainVelocity;

    sf::Time trainInterval;
    sf::Time trainDelay;
    bool delayFlag;
    float trainOffSet;

	Train* train;
    TrainFactory::Ptr trainFactory;
    MyTimer timer;

    RailwayLight* railwayLight;

    void updateCurrent(sf::Time dt);
    void buildLane();

    void createTrain();
    void popTrain();

protected:
    virtual bool isIntoView(Entity* entity, float laneLength) const override;
};

#endif