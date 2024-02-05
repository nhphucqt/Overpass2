#ifndef TRAIN_FACTORY_HPP
#define TRAIN_FACTORY_HPP

#include <Train.hpp>
#include <ResourceID.hpp>

class TrainFactory {
public:
    typedef std::unique_ptr<TrainFactory> Ptr;

private:
    TextureHolder* textures;
    bool isReverse;
    float velocity;
    float laneLength;
    float trainOffSet;

public:
    TrainFactory(TextureHolder* textures, bool isReverse, float velocity, float laneLength, float trainOffSet);
    Train::Ptr createTrain();
};

#endif