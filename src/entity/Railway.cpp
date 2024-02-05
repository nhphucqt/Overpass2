#include <Railway.hpp>
#include <AppConfig.hpp>

const float Railway::TRAIN_VELOCITY = 2000.f;

Railway::Railway(TextureHolder *textures, bool isReverse, float trainInterval, float trainDelay, float trainOffSet, bool isLoad)
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
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(sf::Vector2f(laneLength, cellSize.y));
    setReverse(true);
    type = Lane::Type::Railway;
    textures->get(TextureID::Rail).setRepeated(true);
    sprite.scale(8.f, 8.f);
    sf::IntRect textureRect(0, 0, 1400, 16);
    sprite.setTextureRect(textureRect);
    if (!isLoad)
    {
        buildLane();
    }
}

void Railway::setTrainVelocity(float v)
{
    trainVelocity = v;
}

void Railway::saveLaneData(std::ofstream &outf)
{
    if (outf.is_open()) {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        float f_trainInterval = trainInterval.asSeconds();
        float f_trainDelay = trainDelay.asSeconds();
        float f_trainOffSet = trainOffSet;
        outf.write(reinterpret_cast<const char *>(&f_trainInterval), sizeof(f_trainInterval));
        outf.write(reinterpret_cast<const char *>(&f_trainDelay), sizeof(f_trainDelay));
        outf.write(reinterpret_cast<const char *>(&f_trainOffSet), sizeof(f_trainOffSet));

        outf.write(reinterpret_cast<const char *>(&delayFlag), sizeof(delayFlag));

        bool hasTrain = train != nullptr;
        outf.write(reinterpret_cast<const char *>(&hasTrain), sizeof(hasTrain));
        if (hasTrain) {
            Train::TrainData data = train->serialize();
            outf.write(reinterpret_cast<const char *>(&data), sizeof(data));
        }

        MyTimer::MyTimerData timerData = timer.serialize();
        outf.write(reinterpret_cast<const char *>(&timerData), sizeof(timerData));

        RailwayLight::RailwayLightData railwayLightData = railwayLight->serialize();
        outf.write(reinterpret_cast<const char *>(&railwayLightData), sizeof(railwayLightData));
    }
    else
    {
        std::runtime_error("RAILWAYDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void Railway::loadLaneData(std::ifstream &inf)
{
    if (inf.is_open())
    {
        buildRailwayLight();

        inf.read(reinterpret_cast<char*>(&delayFlag), sizeof(delayFlag));

        bool hasTrain;
        inf.read(reinterpret_cast<char*>(&hasTrain), sizeof(hasTrain));
        if (hasTrain) {
            Train::Ptr trainPtr = std::make_unique<Train>(*laneTextures);

            Train::TrainData data;
            inf.read(reinterpret_cast<char*>(&data), sizeof(data));
            trainPtr->deserialize(data);
            
            train = trainPtr.get();
            attachView(std::move(trainPtr));
        }

        MyTimer::MyTimerData timerData;
        inf.read(reinterpret_cast<char*>(&timerData), sizeof(timerData));

        timer.deserialize(timerData);

        RailwayLight::RailwayLightData railwayLightData;

        inf.read(reinterpret_cast<char*>(&railwayLightData), sizeof(railwayLightData));
        railwayLight->deserialize(railwayLightData);
    }
    else
    {
        std::runtime_error("RAILWAYDATA ERR: \"save.data\" not found.\n");
    }
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
    buildRailwayLight();
    timer.restart();
}

void Railway::buildRailwayLight() {
    RailwayLight::Ptr railwayLightPtr(railwayLight);
    railwayLightPtr->setPosition(laneLength / 2, 0.f);
    attachView(std::move(railwayLightPtr));
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