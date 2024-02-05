#ifndef LOG_FACTORY_HPP
#define LOG_FACTORY_HPP

#include <Log.hpp>
#include <ResourceID.hpp>

class LogFactory {
public:
    typedef std::unique_ptr<LogFactory> Ptr;

private:
    TextureHolder* textures;
    static const int NUM_LEN = 2;
    static const int LOG_LEN[NUM_LEN];
    bool isReverse;
    float velocity;
    float riverLength;
    int __nextLen;

public:
    LogFactory(TextureHolder* textures, bool isReverse, float velocity, float riverLength);
    Log::Ptr createLog();
    int getNextLen();

private:
    void nextLen();
    Log::Type toLogType(int len);
};

#endif