#include <LogFactory.hpp>
#include <MyRandom.hpp>

const int LogFactory::LOG_LEN[NUM_LEN] = {2, 3};

LogFactory::LogFactory(TextureHolder* textures, bool isReverse, float velocity, float riverLength)
: textures(textures), isReverse(isReverse), velocity(velocity), riverLength(riverLength) {
    nextLen();
}

Log::Ptr LogFactory::createLog() {
    Log::Ptr log(new Log(toLogType(getNextLen()), *textures));
    if (isReverse) {
        log->setPosition(riverLength, 0.f);
        log->setVelocity(-velocity, 0.f);
    } else {
        log->setPosition(-log->getSize().x, 0.f);
        log->setVelocity(velocity, 0.f);
    }
    nextLen();
    return std::move(log);
}

int LogFactory::getNextLen() {
    return __nextLen;
}

void LogFactory::nextLen() {
    __nextLen = LOG_LEN[MyRandom::random_range(NUM_LEN)];
}

Log::Type LogFactory::toLogType(int len) {
    switch (len) {
    case 2:
        return Log::Type::WoodL2;
    case 3:
        return Log::Type::WoodL3;
    default:
        return Log::Type::WoodL2;
    }
}