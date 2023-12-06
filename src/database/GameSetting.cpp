#include <GameSetting.hpp>

GameSetting::GameSetting()
    : mSoundPlayer(SoundPlayer::getInstance()), mMusicPlayer(MusicPlayer::getInstance())
{
    loadSettingState("data/settings.txt");
}

GameSetting::~GameSetting()
{
    saveSettingState("data/settings.txt");
}

void GameSetting::loadSettingState(const std::string &filename)
{
    std::ifstream inf(filename);
    if (!inf)
    {
        std::cerr << filename + " not found.\n";
        return;
    }

    float musicVolume;
    float soundVolume;
    inf >> musicVolume >> soundVolume;

    mMusicPlayer.setVolume(musicVolume);
    mSoundPlayer.setVolume(soundVolume);
}

void GameSetting::saveSettingState(const std::string &filename)
{
    std::ofstream outf(filename, std::ofstream::out | std::ofstream::trunc);
    outf << mMusicPlayer.getVolume() << ' ' << mSoundPlayer.getVolume();
}