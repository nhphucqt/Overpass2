#ifndef RESOURCE_ID
#define RESOURCE_ID

#include <ResourceManager.hpp>

enum class TextureID
{
    demoButtonTexture,
    mainMenuButtonTexture,
    mainMenuBackgroundTexture,
    titleBackgroundTexture,
    characterTitleBarTexture,
    squareButtonsTexture,
    toggleButtonsTexture,
    settingMenuTexture,
    iconsTexture,
    Wood,
    Crocodile,
    Car,
    Ambulance,
    Taxi,
    Police,
    Train,
    Bear,
    TrafficLight,
    Tree,
    Bush,
    CircleBush,
    Road,
    River,
    Rail,
    Field,
    Fox,
    Player,
    CharacterUp,
    CharacterDown,
    CharacterLeft,
    CharacterRight,
    CharacterIdle,
    GameOver,
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
    buttonfx,
    buttonClick
};

enum class MusicID
{
    testMusic,
    backgroundMusic
};

typedef ResourceManager<sf::Texture, TextureID> TextureManager;
typedef ResourceManager<sf::Image, ImageID> ImageManager;
typedef ResourceManager<sf::Font, FontID> FontManager;
typedef ResourceManager<sf::SoundBuffer, SoundBufferID> SoundBufferManager;

#endif