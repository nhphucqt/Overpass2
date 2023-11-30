#ifndef RESOURCE_ID
#define RESOURCE_ID

#include "ResourceManager.hpp"

enum class TextureID
{
    demoButtonTexture
};

enum class ImageID
{
};

enum class FontID
{
    defaultFont
};

enum class SoundBufferID
{
    testSound,
    buttonfx
};

enum class MusicID
{
    testMusic
};

typedef ResourceManager<sf::Texture, TextureID> TextureManager;
typedef ResourceManager<sf::Image, ImageID> ImageManager;
typedef ResourceManager<sf::Font, FontID> FontManager;
typedef ResourceManager<sf::SoundBuffer, SoundBufferID> SoundBufferManager;

#endif