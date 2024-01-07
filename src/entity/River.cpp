#include <AppConfig.hpp>
#include <River.hpp>
#include <LogFactory.hpp>

const float River::LOG_TIMER_LOW = 0.5f;
const float River::LOG_TIMER_HIG = 1.5f;
const float River::OUT_OF_VIEW_PADDING = 300.f;

River::River(TextureManager *textures, bool isReverse, float velocity, bool isLoad)
    : Lane(textures->get(TextureID::River), textures, isReverse),
      laneLength(AppConfig::getInstance().get<float>(ConfigKey::LANE_LENGTH)),
      logVelocity(velocity),
      logFactory(std::make_unique<LogFactory>(textures, isReverse, velocity, laneLength)),
      timer(LOG_TIMER_LOW, LOG_TIMER_HIG)
{
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    setSize(sf::Vector2f(laneLength, cellSize.y));
    buildZone();
    type = Lane::Type::River;
    textures->get(TextureID::River).setRepeated(true);
    if (!isLoad) buildLane();
}

void River::setLogVelocity(float v)
{
    logVelocity = v;
}

void River::updateCurrent(sf::Time dt)
{
    while (!logs.empty() && isOutofView(logs.front(), laneLength)) {
        popLog();
    }
    timer.update(dt);
    if (!timer.isTiming() && !logs.empty() && isIntoView(logs.back(), laneLength)) {
        timer.restart();
    }
    if (timer.isTimeout()) {
        timer.stop();
        createLog();
    }
}

void River::buildLane()
{
    createLog();
}

void River::buildZone()
{
    AppConfig &config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    int numLaneCells = config.get<int>(ConfigKey::NumLaneCells);
    detachView(*seqZone);
    SeqZoneRiver::Ptr seqZoneRiver = std::make_unique<SeqZoneRiver>(
        Zone::Type::Dead, cellSize, numLaneCells);
    seqZone = seqZoneRiver.get();
    int numStep = 3;
    int oldSize = seqZone->getNumZone();
    float div = cellSize.x / numStep;
    for (int i = 0; i < oldSize; ++i)
    {
        for (int j = 1; j < oldSize; ++j)
        {
            Zone::Ptr zone = std::make_unique<Zone>(Zone::Type::Dead, cellSize);
            zone->setPosition(sf::Vector2f(i * cellSize.x, 0));
            zone->move(div * j, 0.f);
            seqZone->attachZone(std::move(zone));
        }
    }
    attachView(std::move(seqZoneRiver));
}

void River::createLog() {
    Log::Ptr log = logFactory->createLog();

    logs.push_back(log.get());
    pushLogZones(log.get());
    this->attachView(std::move(log));
}

void River::popLog()
{
    Log *lastLog = logs.front();
    logs.pop_front();
    removeLogZones(lastLog);
    detachView(*lastLog);
}

void River::pushLogZones(Log *log)
{
    SeqZone *logZone = log->getSeqZone();
    for (int i = 0; i < logZone->getNumZone(); ++i)
    {
        seqZone->pushZone(logZone->getZone(i));
    }
}

void River::removeLogZones(Log *log)
{
    SeqZone *logZone = log->getSeqZone();
    for (int i = 0; i < logZone->getNumZone(); ++i)
    {
        seqZone->removeZone(logZone->getZone(i));
    }
}

void River::saveLaneData(std::ofstream& outf) {
    if (outf.is_open()) {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));
        
        outf.write(reinterpret_cast<const char *>(&logVelocity), sizeof(logVelocity));

        int logsSize = logs.size();
        outf.write(reinterpret_cast<const char *>(&logsSize), sizeof(logsSize));

        for (const auto &log : logs) {
            Log::LogData data = log->serialize();
            outf.write(reinterpret_cast<const char *>(&data), sizeof(data));
        }

        MyTimer::MyTimerData timerData = timer.serialize();
        outf.write(reinterpret_cast<const char *>(&timerData), sizeof(timerData));
    } else {
        std::runtime_error("RIVERDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void River::loadLaneData(std::ifstream &inf)
{
    if (inf.is_open())
    {
        int dataSize;
        inf.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
        for (int i = 0; i < dataSize; ++i) {
            Log::LogData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Log> logPtr(new Log(static_cast<Log::Type>(data.type), *laneTextures));
            logPtr->deserialize(data);
            logs.push_back(logPtr.get());
            pushLogZones(logPtr.get());
            this->attachView(std::move(logPtr));
        }

        MyTimer::MyTimerData timerData;
        inf.read(reinterpret_cast<char *>(&timerData), sizeof(timerData));
        timer.deserialize(timerData);
    }
    else
    {
        std::runtime_error("RIVERDATA ERR: \"save.data\" not found.\n");
    }
}

bool River::isOutofView(Entity* entity, float laneLength) const 
{
    return (isReverse && entity->getPosition().x + entity->getSize().x < -OUT_OF_VIEW_PADDING)
        || (!isReverse && entity->getPosition().x > laneLength + OUT_OF_VIEW_PADDING);
}
