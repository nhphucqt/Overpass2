#ifndef LOG_HPP
#define LOG_HPP
#include <Entity.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <SeqZone.hpp>

class Log: public Entity {
public:
    enum Type {Wood, Crocodile};
    Log(Type mType, const TextureManager& textures);
    unsigned int getCategory() const;

    SeqZone* getSeqZone();

private:
    Type type;
    SeqZone* seqZone;
};

#endif