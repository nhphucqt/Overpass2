#include <Railway.hpp>

Railway::Railway(TextureManager *textures, ViewGroup* foreview, bool isReverse):
Lane(textures->get(TextureID::Rail), textures, isReverse), foreground(foreview) {
    type = Lane::Type::Railway;
    textures->get(TextureID::Rail).setRepeated(true);
    sprite.scale(8.f, 8.f);
	sf::IntRect textureRect(0, 0, 1400, 16);
    sprite.setTextureRect(textureRect);
    buildLane();
}

unsigned int Railway::getCategory() const {
    return Category::Lane;
}

void Railway::updateCurrent(sf::Time dt) {
    if (isReverse) {
        if (train->getPosition().x < -1000)
            train->setPosition(train->getPosition().x + 2400 + train->getBoundingRect().width, train->getPosition().y); 
    }
    else {
        if (train->getPosition().x > 2400)
            train->setPosition(train->getPosition().x - 3400, train->getPosition().y); 
    }
}

void Railway::buildLane() {
    std::unique_ptr<Train> mTrain(new Train(*laneTextures));
    mTrain->scale(0.5, 0.5);
    train = mTrain.get();
    if (isReverse) {
        mTrain->scale(-1.f, 1.f);
        mTrain->setPosition(1400.f, 96.f);
        mTrain->setVelocity(-700.f, 0.f);
    }
    else {
        mTrain->setPosition(0.f, 96.f);
        mTrain->setVelocity(700.f, 0.f);
    }
    this->attachView(std::move(mTrain)); 
}