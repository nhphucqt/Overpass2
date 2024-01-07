#include <SoundPlayer.hpp>

SoundPlayer::SoundPlayer()
    : mSoundBuffers(), mSounds(), mVolume(100.0f), mMuted(false)
{
    mSoundBuffers.load(SoundBufferID::buttonClick, "res/sounds/mixkit-classic-click.wav");
    mSoundBuffers.load(SoundBufferID::gameOver, "res/sounds/wrong-buzzer.mp3");

    // ...
}

SoundPlayer &SoundPlayer::getInstance()
{
    static SoundPlayer mSoundPlayer;
    return mSoundPlayer;
}

void SoundPlayer::play(SoundBufferID effect)
{
    mSounds.push_back(sf::Sound(mSoundBuffers.get(effect)));
    mSounds.back().setVolume(getVolume());
    if (mMuted) {
        mSounds.back().setVolume(0);
    }
    mSounds.back().play();
    if (mSounds.size() == 100) {
        removeStoppedSounds();
    }
}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([](const sf::Sound &s)
                      { return s.getStatus() == sf::Sound::Stopped; });
}

void SoundPlayer::setVolume(float volume)
{
    mVolume = volume;
    for (sf::Sound& sound : mSounds) {
        sound.setVolume(volume);
    }
}

float SoundPlayer::getVolume() const
{
    return mVolume;
}

void SoundPlayer::setMute(bool mute)
{
    mMuted = mute;
    if (mute) {
        for (sf::Sound& sound : mSounds) {
            sound.setVolume(0);
        }
    } else {
        for (sf::Sound& sound : mSounds) {
            sound.setVolume(mVolume);
        }
    }
}

bool SoundPlayer::isMuted() const
{
    return mMuted;
}