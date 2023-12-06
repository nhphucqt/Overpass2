#ifndef GAME_SETTING_HPP
#define GAME_SETTING_HPP

#include <SoundPlayer.hpp>
#include <MusicPlayer.hpp>
#include <iostream>
#include <fstream>

class GameSetting
{
public:
    GameSetting(SoundPlayer *soundPlayer, MusicPlayer *musicPlayer);
    ~GameSetting();

    void loadSettingState(const std::string &filename);
    void saveSettingState(const std::string &filename);

private:
    SoundPlayer *mSoundPlayer;
    MusicPlayer *mMusicPlayer;
}

#endif