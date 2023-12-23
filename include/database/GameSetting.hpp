#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

#include <SoundPlayer.hpp>
#include <MusicPlayer.hpp>
#include <iostream>
#include <fstream>

class GameSetting : sf::NonCopyable
{
public:
    ~GameSetting();

    static GameSetting &getInstance();
    GameSetting &operator=(const GameSetting &) = delete;
    GameSetting(const GameSetting &) = delete;

    void loadSettingState();
    void saveSettingState();

private:
    GameSetting();
    void loadSettingState(const std::string &filename);
    void saveSettingState(const std::string &filename);
    SoundPlayer &mSoundPlayer;
    MusicPlayer &mMusicPlayer;
};

#endif