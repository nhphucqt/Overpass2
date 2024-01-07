#ifndef LOG_HPP
#define LOG_HPP

#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SeqZone.hpp>

class Log : public Entity
{
public:
    typedef std::unique_ptr<Log> Ptr;

    enum Type
    {
        WoodL2,
        WoodL3,
        Crocodile,
        Count
    };

    Log(Type mType, const TextureManager &textures);
    unsigned int getCategory() const;

    SeqZone *getSeqZone();

private:
    Type type;
    SeqZone* seqZone;

public:
    struct LogData
    {
        int type;
        float posX;
        float posY;
        float vx;
        float vy;
        float scaleX;
        float scaleY;
    };

    LogData serialize() const;
    void deserialize(LogData &data);
};

#endif
