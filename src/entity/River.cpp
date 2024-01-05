#include <AppConfig.hpp>
#include <River.hpp>
#include <LogFactory.hpp>

const float River::LOG_TIMER_LOW = 0.5f;
const float River::LOG_TIMER_HIG = 1.5f;

River::River(TextureManager *textures, bool isReverse, float velocity)
    : Lane(textures->get(TextureID::River), textures, isReverse),
      laneLength(AppConfig::getInstance().get<float>(ConfigKey::LANE_LENGTH)),
      logVelocity(velocity),
      logFactory(std::make_unique<LogFactory>(textures, isReverse, velocity, laneLength)),
      timer(LOG_TIMER_LOW, LOG_TIMER_HIG)
{
    buildZone();
    type = Lane::Type::River;
    textures->get(TextureID::River).setRepeated(true);
    buildLane();
}

void River::setLogVelocity(float v)
{
    logVelocity = v;
}

void River::updateCurrent(sf::Time dt)
{
    while (!logs.empty() && isLogOutOfView(logs.front())) {
        popLog();
    }

    timer.update(dt);

    if (!timer.isTiming() && !logs.empty() && isLogIntoView(logs.back())) {
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

    logs.push(log.get());
    pushLogZones(log.get());
    this->attachView(std::move(log));
}

void River::popLog()
{
    Log *lastLog = logs.front();
    logs.pop();
    removeLogZones(lastLog);
    detachView(*lastLog);
    // std::cerr << "remove log" << std::endl;
}

bool River::isLogOutOfView(Log *log)
{
    return (isReverse && log->getPosition().x + log->getSize().x < 0)
        || (!isReverse && log->getPosition().x > laneLength);
}

bool River::isLogIntoView(Log *log)
{
    return (!isReverse && log->getPosition().x > 0)
        || (isReverse && log->getPosition().x + log->getSize().x < laneLength);
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

