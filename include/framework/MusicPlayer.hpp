#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <ResourceID.hpp>

class MusicPlayer : private sf::NonCopyable
{
public:
    MusicPlayer();
    void play(MusicID theme);
    void stop();
    void setPaused(bool paused);
    void setVolume(float volume);

private:
    sf::Music mMusic;
    std::map<MusicID, std::string> mFilenames;
    float mVolume;
};

#endif