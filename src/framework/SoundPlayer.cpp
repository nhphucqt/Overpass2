#include <SoundPlayer.hpp>

SoundPlayer::SoundPlayer()
    : mSoundBuffers(), mSounds(), mVolume(100.0f)
{
    mSoundBuffers.load(SoundBufferID::testSound, "res/sounds/door-open-sound-effect-94368.ogg");
    mSoundBuffers.load(SoundBufferID::buttonfx, "res/sounds/buttonfx.wav");
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

void SoundPlayer::setVolume(float volume)
{
    mVolume = volume;
}

float SoundPlayer::getVolume() const
{
    return mVolume;
}