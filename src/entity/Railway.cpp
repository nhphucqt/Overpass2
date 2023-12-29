#include <Railway.hpp>

namespace DEFAULT {
    const float LANELENGTH = 1400.f;
    const float PADDING = 1000.f;
    const float TRAINVELOCITY = 700.f;
};

Railway::Railway(TextureManager *textures, ViewGroup* foreview, bool isReverse)
: Lane(textures->get(TextureID::Rail), textures, isReverse), foreground(foreview)
, laneLength(DEFAULT::LANELENGTH)
, padding(DEFAULT::PADDING)
, trainVelocity(DEFAULT::TRAINVELOCITY)
{
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
    if (isReverse && train->getPosition().x < -padding)
        train->setPosition(train->getPosition().x + laneLength + padding + train->getBoundingRect().width, train->getPosition().y); 
    else if (!isReverse && train->getPosition().x > laneLength + padding)
            train->setPosition(train->getPosition().x - laneLength - 2 * padding, train->getPosition().y); 
}

void Railway::buildLane() {
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