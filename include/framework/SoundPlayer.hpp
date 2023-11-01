#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <SFML/Audio.hpp>
#include <cassert>
#include <list>

class SoundPlayer : private sf::NonCopyable {
public:
  SoundPlayer();
  void play(SoundBufferID effect);
  void removeStoppedSounds();

private:
  SoundBufferManager mSoundBuffers;
  std::list<sf::Sound> mSounds;
};

#endif