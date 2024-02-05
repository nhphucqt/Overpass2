#ifndef RESOURCE_ID
#define RESOURCE_ID

#include <ResourceHolder.hpp>

enum class TextureID
{
    mainMenuButtonTexture,
    mainMenuBackgroundTexture,
    titleBackgroundTexture,
    characterTitleBarTexture,
    squareButtonsTexture,
    homeButtonsTexture,
    continueButtonsTexture,
    pauseButtonsTexture,
    settingButtonsTexture,
    replayButtonsTexture,
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
    Supercar,

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
    buttonClick,
    gameOver
};

enum class MusicID
{
    backgroundMusic
};

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;
typedef ResourceHolder<sf::Image, ImageID> ImageHolder;
typedef ResourceHolder<sf::Font, FontID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundBufferID> SoundBufferHolder;

#endif
