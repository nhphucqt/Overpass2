#include <TrainFactory.hpp>
#include <MyRandom.hpp>

TrainFactory::TrainFactory(TextureHolder* textures, bool isReverse, float velocity, float laneLength, float trainOffSet)
: textures(textures), isReverse(isReverse), velocity(velocity), laneLength(laneLength), trainOffSet(trainOffSet) {
}

Train::Ptr TrainFactory::createTrain() {
    Train::Ptr train(new Train(*textures));
    if (isReverse) {
        train->reverseSprite();
        train->setPosition(laneLength, 0.f);
        train->setVelocity(-velocity, 0.f);
        train->move(trainOffSet, 0.f);
    } else {
        train->setPosition(-train->getSize().x, 0.f);
        train->setVelocity(velocity, 0.f);
        train->move(-trainOffSet, 0.f);
    }
    return std::move(train);
}