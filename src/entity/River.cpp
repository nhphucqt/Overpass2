#include <River.hpp>
#include <AppConfig.hpp>

namespace DEFAULT {
    const float LANELENGTH = 1400.f;
    const float PADDING = 100.f;
    const int NUMOFLOG = 3;
    const float LOGVELOCITY = 200.f;
};

River::River(TextureManager *textures, bool isReverse)
: Lane(textures->get(TextureID::River), textures, isReverse)
, laneLength(DEFAULT::LANELENGTH)
, padding(DEFAULT::PADDING)
, numOfLog(DEFAULT::NUMOFLOG)
, logVelocity(DEFAULT::LOGVELOCITY)
{
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    int numLaneCells = config.get<int>(ConfigKey::NumLaneCells);
    detachView(*seqZone);
    SeqZoneRiver::Ptr seqZoneRiver = std::make_unique<SeqZoneRiver>(Zone::Type::Dead, cellSize, numLaneCells);
    seqZone = seqZoneRiver.get();
    attachView(std::move(seqZoneRiver));

    type = Lane::Type::River;
    textures->get(TextureID::River).setRepeated(true);
    buildLane();
}

void River::setNumOfLog(int n) {
    numOfLog = n;
}

void River::setlogVelocity(float v) {
    logVelocity = v;
}

void River::updateCurrent(sf::Time dt) {
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // log circling when out of view
    Log* lastLog = logs.back();
    Log* firstLog = logs.front();
    int distance = laneLength/logs.size();
    if ((isReverse && lastLog->getPosition().x < -padding) || (!isReverse && lastLog->getPosition().x > laneLength + padding))
        logs[logs.size() - 1]->setPosition(firstLog->getPosition().x - padding * reverseScale - distance * reverseScale, lastLog->getPosition().y);
    // make the last car becomes the first car in the next iteration
    logs.pop_back();
    logs.insert(logs.begin(), lastLog);
}

void River::buildLane() {
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // creating vehicles, vehicles should have the same type for consisteny
    for (int i = 0; i < numOfLog; ++i) {
        std::unique_ptr<Log> log(new Log(Log::Wood, *laneTextures));
        logs.push_back(log.get());
        log->setVelocity(logVelocity * reverseScale, 0.f);
        // log->scale(reverseScale, 1);
        pushLogZones(log.get());
        this->attachView(std::move(log));
    }

    // reverse log vector for updateCurrent
    if (isReverse) {
        std::reverse(logs.begin(), logs.end());
    }
}

void River::pushLogZones(Log* log) {
    SeqZone* logZone = log->getSeqZone();
    for (int i = 0; i < logZone->getNumZone(); ++i) {
        seqZone->pushZone(logZone->getZone(i));
    }
}

void River::removeLogZones(Log* log) {
    SeqZone* logZone = log->getSeqZone();
    for (int i = 0; i < logZone->getNumZone(); ++i) {
        seqZone->removeZone(logZone->getZone(i));
    }
}