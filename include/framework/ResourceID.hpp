#ifndef RESOURCE_ID
#define RESOURCE_ID

#include "ResourceManager.hpp"

enum class TextureID
{
};

enum class ImageID
{
};

enum class FontID
{
};

enum class SoundBufferID
{
};

enum class MusicID
{
};

typedef ResourceManager<sf::Texture, TextureID> TextureManager;
typedef ResourceManager<sf::Image, ImageID> ImageManager;
typedef ResourceManager<sf::Font, FontID> FontManager;
typedef ResourceManager<sf::SoundBuffer, SoundBufferID> SoundBufferManager;

#endif