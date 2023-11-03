#include <SoundPlayer.hpp>

SoundPlayer::SoundPlayer()
    : mSoundBuffers(), mSounds()
{
    mSoundBuffers.load(SoundBufferID::testSound, "res/sounds/door-open-sound-effect-94368.ogg");
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