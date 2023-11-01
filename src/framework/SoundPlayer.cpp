#include <SoundPlayer.hpp>

SoundPlayer::SoundPlayer()
    : mSoundBuffers(), mSounds()
{
    // mSoundBuffer.load(SoundBufferID::ObjectID, "[path to object sound]");
    // ...
}

void SoundPlayer::play(SoundBufferID effect)
{
    mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
    mSounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([](const sf::Sound &s)
                      { return s.getStatus() == sf::Sound::Stopped; });
}