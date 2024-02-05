#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <ResourceID.hpp>
#include <ResourceHolder.hpp>
#include <list>
#include <cassert>

class SoundPlayer : private sf::NonCopyable
{
public:
    static SoundPlayer &getInstance();
    SoundPlayer(const SoundPlayer &) = delete;
    SoundPlayer &operator=(const SoundPlayer &) = delete;

    void play(SoundBufferID effect);
    void removeStoppedSounds();

    void setVolume(float volume);
    float getVolume() const;

    void setMute(bool mute);
    bool isMuted() const;

private:
    SoundPlayer();

    SoundBufferHolder mSoundBuffers;
    std::list<sf::Sound> mSounds;
    float mVolume;
    bool mMuted;
};

#endif