#include <Railway.hpp>

Railway::Railway(TextureManager *textures, ViewGroup* foreview, bool isReverse, bool isLoad):
Lane(textures->get(TextureID::Rail), textures, isReverse), foreground(foreview) {
    type = Lane::Type::Railway;
    textures->get(TextureID::Rail).setRepeated(true);
    sprite.scale(8.f, 8.f);
	sf::IntRect textureRect(0, 0, 1400, 16);
    sprite.setTextureRect(textureRect);
    if (!isLoad) {
        buildLane();
    }
}

unsigned int Railway::getCategory() const {
    return Category::Lane;
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

void Railway::saveLaneData(std::ofstream& outf) {
    if (outf.is_open()) {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char*>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char*>(&isReverse), sizeof(isReverse));

        Train::TrainData data = train->serialize();
        outf.write(reinterpret_cast<const char*>(&data), sizeof(data));
    } else {
        std::runtime_error("RAILWAYDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void Railway::loadLaneData(std::ifstream& inf) {
    if (inf.is_open()) {
        // int nType;
        // bool nIsReverse;
        // inf.read(reinterpret_cast<char*>(&nType), sizeof(nType));
        // inf.read(reinterpret_cast<char*>(&nIsReverse), sizeof(nIsReverse));
        
        Train::TrainData data;
        inf.read(reinterpret_cast<char*>(&data), sizeof(data));
        std::cout << "train is at: " << data.posX << ' ' << data.posY << std::endl;

        std::unique_ptr<Train> mTrain(new Train(*laneTextures));
        train = mTrain.get();
        mTrain->deserialize(data);
        this->attachView(std::move(mTrain)); 
    } else {
        std::runtime_error("RAILWAYDATA ERR: \"save.data\" not found.\n");
    }
}