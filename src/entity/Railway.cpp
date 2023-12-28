#include <Railway.hpp>

namespace DEFAULT
{
    const float LANELENGTH = 1400.f;
    const float PADDING = 1000.f;
    const float TRAINVELOCITY = 700.f;
};

Railway::Railway(TextureManager *textures, ViewGroup *foreview, bool isReverse, bool isLoad)
    : Lane(textures->get(TextureID::Rail), textures, isReverse), foreground(foreview), laneLength(DEFAULT::LANELENGTH), padding(DEFAULT::PADDING), trainVelocity(DEFAULT::TRAINVELOCITY)
{
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

void Railway::updateCurrent(sf::Time dt)
{
    if (isReverse && train->getPosition().x < -padding)
        train->setPosition(train->getPosition().x + laneLength + padding + train->getBoundingRect().width, train->getPosition().y);
    else if (!isReverse && train->getPosition().x > laneLength + padding)
        train->setPosition(train->getPosition().x - laneLength - 2 * padding, train->getPosition().y);
}

void Railway::buildLane()
{
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    std::unique_ptr<Train> mTrain(new Train(*laneTextures));
    train = mTrain.get();
    mTrain->scale(reverseScale, 1.f);
    mTrain->setPosition(laneLength * isReverse, 96.f);
    mTrain->setVelocity(trainVelocity * reverseScale, 0.f);
    this->attachView(std::move(mTrain));
}

void Railway::saveLaneData(const std::string &filename)
{
    std::ofstream outf(filename, std::ios::binary);
    if (outf.is_open())
    {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        Train::TrainData data;
        data.trainPosX = train->getPosition().x;
        data.trainPosY = train->getPosition().y;
        outf.write(reinterpret_cast<const char *>(&data), sizeof(data));

        outf.close();
    }
    else
    {
        std::runtime_error("RAILWAYDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void Railway::loadLaneData(const std::string &filename)
{
    std::ifstream inf(filename, std::ios::binary);
    if (inf.is_open())
    {
        int nType;
        bool nIsReverse;
        inf.read(reinterpret_cast<char *>(&nType), sizeof(nType));
        inf.read(reinterpret_cast<char *>(&nIsReverse), sizeof(nIsReverse));

        Train::TrainData data;
        inf.read(reinterpret_cast<char *>(&data), sizeof(data));
        inf.close();
        std::cout << "train is at: " << data.trainPosX << ' ' << data.trainPosY << std::endl;

        std::unique_ptr<Train> mTrain(new Train(*laneTextures));
        mTrain->scale(0.5, 0.5);
        train = mTrain.get();
        if (nIsReverse)
        {
            mTrain->scale(-1.f, 1.f);
            mTrain->setPosition(data.trainPosX, data.trainPosY);
            mTrain->setVelocity(-700.f, 0.f);
        }
        else
        {
            mTrain->setPosition(data.trainPosX, data.trainPosY);
            mTrain->setVelocity(700.f, 0.f);
        }
        this->attachView(std::move(mTrain));
    }
    else
    {
        std::runtime_error("RAILWAYDATA ERR: " + filename + " not found.\n");
    }
}

void Railway::saveLaneData(const std::string &filename)
{
    std::ofstream outf(filename, std::ios::binary);
    if (outf.is_open())
    {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        Train::TrainData data = train->serialize();
        outf.write(reinterpret_cast<const char *>(&data), sizeof(data));

        outf.close();
    }
    else
    {
        std::runtime_error("RAILWAYDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void Railway::loadLaneData(const std::string &filename)
{
    std::ifstream inf(filename, std::ios::binary);
    if (inf.is_open())
    {
        int nType;
        bool nIsReverse;
        inf.read(reinterpret_cast<char *>(&nType), sizeof(nType));
        inf.read(reinterpret_cast<char *>(&nIsReverse), sizeof(nIsReverse));

        Train::TrainData data;
        inf.read(reinterpret_cast<char *>(&data), sizeof(data));
        inf.close();
        std::cout << "train is at: " << data.posX << ' ' << data.posY << std::endl;

        std::unique_ptr<Train> mTrain(new Train(*laneTextures));
        mTrain->deserialize(data);
        this->attachView(std::move(mTrain));
    }
    else
    {
        std::runtime_error("RAILWAYDATA ERR: " + filename + " not found.\n");
    }
}