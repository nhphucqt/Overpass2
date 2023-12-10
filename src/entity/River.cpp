#include <River.hpp>

River::River(TextureManager *textures, bool isReverse):
Lane(textures->get(TextureID::River), textures, isReverse) {
    buildLane();
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
    if (isReverse) {
        std::unique_ptr<Log> log(new Log(Log::Wood, *laneTextures));
        logs.push_back(log.get());
        log->setPosition(1400.f, 64.f);
        log->setVelocity(-150.f, 0.f);
        log->scale(0.8, 0.8);
        this->attachView(std::move(log)); 
    }
    else {
        std::unique_ptr<Log> log(new Log(Log::Wood, *laneTextures));
        logs.push_back(log.get());
        log->setPosition(0.f, 64.f);
        log->setVelocity(150.f, 0.f);
        log->scale(0.8, 0.8);
        this->attachView(std::move(log));
    }

}