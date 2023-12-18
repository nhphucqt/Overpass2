#include <MusicPlayer.hpp>

MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(100.0f)
{
  // Example
  mFilenames[MusicID::testMusic] = "res/musics/fellowship.mp3";
  mFilenames[MusicID::backgroundMusic] = "res/musics/cruising-down-8bit-lane.mp3";
  // mFilenames[MusicID::MissionTheme] = "[path to mission theme]";
}

MusicPlayer &MusicPlayer::getInstance()
{
  static MusicPlayer mMusicPlayer;
  return mMusicPlayer;
}

void MusicPlayer::play(MusicID theme)
{
  std::string filename = mFilenames[theme];
  if (!mMusic.openFromFile(filename))
    throw std::runtime_error("Music " + filename + " could not be loaded.");
  mMusic.setVolume(mVolume);
  mMusic.setLoop(true);
  mMusic.play();
}

void MusicPlayer::stop() { mMusic.stop(); }

void MusicPlayer::setPaused(bool paused)
{
  if (paused)
    mMusic.pause();
  else
    mMusic.play();
}

void MusicPlayer::setVolume(float volume)
{
  mVolume = volume;
}

float MusicPlayer::getVolume() const
{
  return mVolume;
}
