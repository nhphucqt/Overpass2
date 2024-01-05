#include <AppConfig.hpp>
#include <River.hpp>

namespace DEFAULT
{
    const float LANELENGTH = 1400.f;
    const float PADDING = 100.f;
    const int NUMOFLOG = 3;
    const float LOGVELOCITY = 200.f;
}; // namespace DEFAULT

River::River(TextureManager *textures, bool isReverse, float velocity)
    : Lane(textures->get(TextureID::River), textures, isReverse),
      laneLength(DEFAULT::LANELENGTH),
      padding(DEFAULT::PADDING),
      numOfLog(DEFAULT::NUMOFLOG),
      logVelocity(velocity)
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

    type = Lane::Type::River;
    textures->get(TextureID::River).setRepeated(true);
    if (!isLoad)
    {
        buildLane();
    }
}

void River::setNumOfLog(int n)
{
    numOfLog = n;
}

void River::setLogVelocity(float v)
{
    logVelocity = v;
}

void River::updateCurrent(sf::Time dt)
{
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // log circling when out of view
    Log *lastLog = logs.back();
    Log *firstLog = logs.front();
    int distance = laneLength / logs.size();
    Log *lastLog = logs.back();
    Log *firstLog = logs.front();
    int distance = laneLength / logs.size();
    if ((isReverse && lastLog->getPosition().x < -padding) || (!isReverse && lastLog->getPosition().x > laneLength + padding))
    {
        logs[logs.size() - 1]->setPosition(firstLog->getPosition().x - padding * reverseScale - distance * reverseScale,
                                           lastLog->getPosition().y);
    }
    // make the last car becomes the first car in the next iteration
    // logs.erase(logs.end());
    std::rotate(logs.rbegin(), logs.rbegin() + 1, logs.rend());
    std::rotate(logs.rbegin(), logs.rbegin() + 1, logs.rend());
}

void River::buildLane()
{
    // set up variables for reverse
    int reverseScale;
    (isReverse) ? reverseScale = -1 : reverseScale = 1;

    // creating vehicles, vehicles should have the same type for consisteny
    for (int i = 0; i < numOfLog; ++i)
    {
        std::unique_ptr<Log> log(new Log(Log::Wood, *laneTextures));
        logs.push_back(log.get());
        log->setVelocity(logVelocity * reverseScale, 0.f);
        // log->scale(reverseScale, 1);
        pushLogZones(log.get());
        this->attachView(std::move(log));
    }

    // reverse log vector for updateCurrent
    if (isReverse)
    {
        std::reverse(logs.begin(), logs.end());
    }
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

void River::saveLaneData(const std::string &filename)
{
    std::ofstream outf(filename, std::ios::binary);
    if (outf.is_open())
    {
        int castedType = static_cast<int>(type);
        outf.write(reinterpret_cast<const char *>(&castedType), sizeof(castedType));
        outf.write(reinterpret_cast<const char *>(&isReverse), sizeof(isReverse));

        int dataSize = logs.size();
        outf.write(reinterpret_cast<const char *>(&dataSize), sizeof(dataSize));

        for (const auto &log : logs)
        {
            Log::LogData data = log->serialize();
            outf.write(reinterpret_cast<const char *>(&data), sizeof(data));
        }
    }
    else
    {
        std::runtime_error("RIVERDATA ERR: \"save.data\" cannot be openned.\n");
    }
}

void River::loadLaneData(std::ifstream &inf)
{
    if (inf.is_open())
    {
        // int nType;
        // bool nIsReverse;
        // inf.read(reinterpret_cast<char *>(&nType), sizeof(nType));
        // inf.read(reinterpret_cast<char *>(&nIsReverse), sizeof(nIsReverse));

        int dataSize;
        inf.read(reinterpret_cast<char *>(&dataSize), sizeof(dataSize));
        std::cout << "log size: " << dataSize << std::endl;

        for (int i = 0; i < dataSize; ++i)
        {
            Log::LogData data;
            inf.read(reinterpret_cast<char *>(&data), sizeof(data));
            std::unique_ptr<Log> logPtr(new Log(static_cast<Log::Type>(data.type), *laneTextures));
            logPtr->deserialize(data);
            logs.push_back(logPtr.get());
            this->attachView(std::move(logPtr));
        }
    }
    else
    {
        std::runtime_error("RIVERDATA ERR: \"save.data\" not found.\n");
    }
}