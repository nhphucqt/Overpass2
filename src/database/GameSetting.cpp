#include <GameSetting.hpp>

GameSetting::GameSetting()
    : mSoundPlayer(SoundPlayer::getInstance()), mMusicPlayer(MusicPlayer::getInstance())
{
}

GameSetting::~GameSetting()
{
}

GameSetting& GameSetting::getInstance() {
    static GameSetting gameSetting;
    return gameSetting;
}

void GameSetting::loadSettingState() {
    loadSettingState("data/settings.txt");
}

void GameSetting::loadSettingState(const std::string &filename)
{
    std::ifstream inf(filename);
    if (!inf)
    {
        std::cerr << filename + " not found.\n";
        std::cerr << "Initialize the data...\n";
        saveSettingState(filename);
        loadSettingState(filename);
        return;
    }

    int musicMuted;
    int soundMuted;
    inf >> musicMuted >> soundMuted;

    mMusicPlayer.setMute(musicMuted);
    mSoundPlayer.setMute(soundMuted);
    // mMusicPlayer.setVolume(musicVolume);
    // mSoundPlayer.setVolume(soundVolume);

    inf.close();
}

void GameSetting::saveSettingState() {
    saveSettingState("data/settings.txt");
}

void GameSetting::saveSettingState(const std::string &filename)
{
    std::ofstream outf(filename, std::ofstream::out | std::ofstream::trunc);
    // outf << mMusicPlayer.getVolume() << ' ' << mSoundPlayer.getVolume();
    outf << mMusicPlayer.isMuted() << ' ' << mSoundPlayer.isMuted();
    outf.close();
}