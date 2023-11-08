#include <MusicPlayer.hpp>

MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(100.0f)
{
  // Example
  mFilenames[MusicID::testMusic] = "res/musics/hypnotic-heartbeat-atmosphere-freqman-cliche-hypnotic-6068.ogg";
  // mFilenames[MusicID::MissionTheme] = "[path to mission theme]";
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