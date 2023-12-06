#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <list>
#include <cassert>

class SoundPlayer : private sf::NonCopyable
{
public:
    SoundPlayer();
    void play(SoundBufferID effect);
    void removeStoppedSounds();
    void setVolume(float volume);

    float getVolume() const;

private:
    SoundBufferManager mSoundBuffers;
    std::list<sf::Sound> mSounds;
    float mVolume;
};

#endif