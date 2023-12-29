#include <River.hpp>

River::River(TextureManager *textures, bool isReverse, bool isLoad) : Lane(textures->get(TextureID::River), textures, isReverse) {
    type = Lane::Type::River;
    textures->get(TextureID::River).setRepeated(true);
    if (!isLoad) {
        buildLane();
    }
}

unsigned int River::getCategory() const {
    return Category::River;
}

void River::updateCurrent(sf::Time dt) {
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // log circling when out of view
    Log *lastLog = logs.back();
    Log *firstLog = logs.front();
    int distance = laneLength / logs.size();
    if ((isReverse && lastLog->getPosition().x < -padding) || (!isReverse && lastLog->getPosition().x > laneLength + padding))
        logs[logs.size() - 1]->setPosition(firstLog->getPosition().x - padding * reverseScale - distance * reverseScale, lastLog->getPosition().y);
	std::cout << "river is fine1\n";
    // make the last car becomes the first car in the next iteration
    // logs.erase(logs.end());
    std::rotate(logs.rbegin(), logs.rbegin() + 1, logs.rend());
	std::cout << "river is fine2\n";
}

void River::buildLane() {
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // creating vehicles, vehicles should have the same type for consisteny
    for (int i = 0; i < numOfLog; ++i) {
        std::unique_ptr<Log> log(new Log(Log::Wood, *laneTextures));
        logs.push_back(log.get());
        log->setPosition((laneLength + 100) / numOfLog * i, 64.f);
        log->setVelocity(logVelocity * reverseScale, 0.f);
        log->scale(reverseScale, 1);
        this->attachView(std::move(log));
    }

    // reverse log vector for updateCurrent
    if (isReverse) {
        std::reverse(logs.begin(), logs.end());
    }
}

void River::saveLaneData(const std::string &filename) {
    std::ofstream outf(filename, std::ios::binary);
    if (outf.is_open()) {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        int dataSize = logs.size();
        outf.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));

        for (const auto &log : logs) {
            Log::LogData data = log->serialize();
            outf.write(reinterpret_cast<const char *>(&data), sizeof(data));
        }

        outf.close();
    } else {
        std::runtime_error("RIVERDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void River::loadLaneData(const std::string &filename) {
    std::ifstream inf(filename, std::ios::binary);
    if (inf.is_open()) {
        int nType;
        bool nIsReverse;
        inf.read(reinterpret_cast<char *>(&nType), sizeof(nType));
        inf.read(reinterpret_cast<char *>(&nIsReverse), sizeof(nIsReverse));

        int dataSize;
        inf.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
        std::cout << "log size: " << dataSize << std::endl;

        for (int i = 0; i < dataSize; ++i) {
            Log::LogData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Log> logPtr(new Log(static_cast<Log::Type>(data.type), *laneTextures));
            logPtr->deserialize(data);
            logs.push_back(logPtr.get());
            this->attachView(std::move(logPtr));
        }

        inf.close();
    } else {
        std::runtime_error("RIVERDATA ERR: " + filename + " not found.\n");
    }
}