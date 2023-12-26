#include <River.hpp>

River::River(TextureManager *textures, bool isReverse, bool isLoad):
Lane(textures->get(TextureID::River), textures, isReverse) {
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
    if (isReverse) {
        Log* lastLog = logs[logs.size() - 1];
        Log* firstLog = logs[0];
        int distance = 1400/logs.size();
        if (lastLog->getPosition().x < -200)
            logs[logs.size() - 1]->setPosition(firstLog->getPosition().x + 450 + distance, lastLog->getPosition().y); 
    }
    else {
        Log* lastLog = logs[logs.size() - 1];
        Log* firstLog = logs[0];
        int distance = 1400/logs.size();
        if (lastLog->getPosition().x > 1600)
            logs[logs.size() - 1]->setPosition(firstLog->getPosition().x - 450 - distance, lastLog->getPosition().y);
    }
}

void River::buildLane() {
    std::unique_ptr<Log> log(new Log(Log::Wood, *laneTextures));
    logs.push_back(log.get());
    if (isReverse) {
        log->setPosition(1400.f, 64.f);
        log->setVelocity(-150.f, 0.f);
    }
    else {
        log->setPosition(0.f, 64.f);
        log->setVelocity(150.f, 0.f);
    }
    this->attachView(std::move(log)); 

}

void River::saveLaneData(const std::string& filename) {
    std::ofstream outf(filename, std::ios::binary);
    if (outf.is_open()) {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char*>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char*>(&isReverse), sizeof(isReverse));

        int dataSize = logs.size();
        outf.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));

        for (const auto& log : logs) {
            Log::LogData data = log->serialize();
            outf.write(reinterpret_cast<const char*>(&data), sizeof(data));    
        }

        outf.close();
    } else {
        std::runtime_error("RIVERDATA ERR: " + filename + " cannot be openned.\n");
    }
}

void River::loadLaneData(const std::string& filename) {
    std::ifstream inf(filename, std::ios::binary);
    if (inf.is_open()) {
        int nType;
        bool nIsReverse;
        inf.read(reinterpret_cast<char*>(&nType), sizeof(nType));
        inf.read(reinterpret_cast<char*>(&nIsReverse), sizeof(nIsReverse));

        int dataSize;
        inf.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        std::cout << "log size: " << dataSize << std::endl;
        
        for (int i = 0; i < dataSize; ++i) {
            Log::LogData data;
            inf.read(reinterpret_cast<char*>(&data), sizeof(data));
            std::unique_ptr<Log> logPtr(new Log(static_cast<Log::Type>(data.type), *laneTextures));
            logPtr->deserialize(data);
            logs.push_back(logPtr.get());
            if (nIsReverse) {
                logPtr->setVelocity(-150.f, 0.f);
            } else {
                logPtr->setVelocity(150.f, 0.f);
            }
            this->attachView(std::move(logPtr));
        }

        inf.close();
    } else {
        std::runtime_error("RIVERDATA ERR: " + filename + " not found.\n");
    }
}