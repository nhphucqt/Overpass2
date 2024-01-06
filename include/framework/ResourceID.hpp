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
    rankingTitleTexture,

    // lanes
    Road,
    River,
    Rail,
    Field,

    // logs
    WoodL2,
    WoodL3,
    Crocodile,

    // vehicles
    Car,
    Ambulance,
    Taxi,
    Police,

    // train
    Train,

    // animals
    Bear,
    Boar,
    Bunny,
    Deer,
    Fox,
    Wolf,

    // traffic light
    TrafficLight,
    RailwayLightOff,
    RailwayLightOn,

    // greens aka plants
    Tree,
    Bush,
    CircleBush,

    // character animation panes
    CharacterUp,
    CharacterDown,
    CharacterLeft,
    CharacterRight,
    CharacterIdle,

    // game over banner
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
