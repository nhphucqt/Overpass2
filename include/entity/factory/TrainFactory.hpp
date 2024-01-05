#ifndef TRAIN_FACTORY_HPP
#define TRAIN_FACTORY_HPP

#include <Train.hpp>
#include <ResourceID.hpp>

class TrainFactory {
public:
    typedef std::unique_ptr<TrainFactory> Ptr;

private:
    TextureManager* textures;
    bool isReverse;
    float velocity;
    float laneLength;
    float trainOffSet;

public:
    TrainFactory(TextureManager* textures, bool isReverse, float velocity, float laneLength, float trainOffSet);
    Train::Ptr createTrain();
};

#endif