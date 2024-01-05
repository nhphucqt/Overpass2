#ifndef LOG_FACTORY_HPP
#define LOG_FACTORY_HPP

#include <Log.hpp>
#include <ResourceID.hpp>

class LogFactory {
public:
    typedef std::unique_ptr<LogFactory> Ptr;

private:
    TextureManager* textures;
    static const int NUM_LEN = 2;
    static const int LOG_LEN[NUM_LEN];
    bool isReverse;
    float velocity;
    int riverLength;
    int __nextLen;

public:
    LogFactory(TextureManager* textures, bool isReverse, float velocity, int riverLength);
    Log::Ptr createLog();
    int getNextLen();

private:
    void nextLen();
    Log::Type toLogType(int len);
};

#endif