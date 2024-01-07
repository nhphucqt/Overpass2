#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <ResourceID.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

class MusicPlayer : private sf::NonCopyable
{
public:
  static MusicPlayer &getInstance();
  MusicPlayer &operator=(const MusicPlayer &) = delete;
  MusicPlayer(const MusicPlayer &) = delete;

  void play(MusicID theme);
  void stop();
  void setPaused(bool paused);

  void setVolume(float volume);
  float getVolume() const;

  void setMute(bool mute);
  bool isMuted() const;

private:
  MusicPlayer();

  sf::Music mMusic;
  std::map<MusicID, std::string> mFilenames;
  float mVolume;
  bool mMuted;
};

#endif