#include <Railway.hpp>
#include <AppConfig.hpp>

const float Railway::TRAIN_VELOCITY = 2000.f;

Railway::Railway(TextureManager *textures, bool isReverse, float trainInterval, float trainDelay, float trainOffSet)
: Lane(textures->get(TextureID::Rail), textures, isReverse)
, laneLength(AppConfig::getInstance().get<float>(ConfigKey::LANE_LENGTH))
, trainVelocity(TRAIN_VELOCITY)
, trainInterval(sf::seconds(trainInterval))
, trainDelay(sf::seconds(trainDelay))
, trainOffSet(trainOffSet)
, trainFactory(std::make_unique<TrainFactory>(textures, isReverse, trainVelocity, laneLength, trainOffSet))
, timer(trainDelay, trainDelay)
, delayFlag(true)
, train(nullptr)
, railwayLight(new RailwayLight(*textures))
{
    setReverse(true);
    type = Lane::Type::Railway;
    textures->get(TextureID::Rail).setRepeated(true);
    sprite.scale(8.f, 8.f);
	sf::IntRect textureRect(0, 0, 1400, 16);
    sprite.setTextureRect(textureRect);
    buildLane();
}

void Railway::setTrainVelocity(float v) {
    trainVelocity = v;
}

void Railway::updateCurrent(sf::Time dt) {
    if (train != nullptr && isOutofView(train, laneLength)) {
        popTrain();
    }

    if (train != nullptr && isIntoView(train, laneLength)) {
        railwayLight->turnOff();
    }

    timer.update(dt);

    if (train == nullptr && timer.isTimeout()) {
        createTrain();
        railwayLight->turnOn();
        if (delayFlag) {
            timer = MyTimer(trainInterval.asSeconds(), trainInterval.asSeconds());
            delayFlag = false;
        }
        timer.restart();
    }
}

void Railway::buildLane() {
    RailwayLight::Ptr railwayLightPtr(railwayLight);
    railwayLightPtr->setPosition(laneLength / 2, 0.f);
    attachView(std::move(railwayLightPtr));
    timer.restart();
}

void Railway::createTrain() {
    Train::Ptr trainPtr = trainFactory->createTrain();
    train = trainPtr.get();
    attachView(std::move(trainPtr));
}

void Railway::popTrain() {
    detachView(*train);
    train = nullptr;
}

bool Railway::isIntoView(Entity* entity, float laneLength) const {
    return (!isReverse && entity->getPosition().x + entity->getSize().x > 0)
        || (isReverse && entity->getPosition().x < laneLength);
}