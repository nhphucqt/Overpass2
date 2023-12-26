#include <UserData.hpp>

UserData::UserData(std::string username, std::string password, int easy, int medium, int hard, int endless)
    : username(username), password(password)
{
    highscore.at(GameMode::easy) = easy;
    highscore.at(GameMode::medium) = medium;
    highscore.at(GameMode::hard) = hard;
    highscore.at(GameMode::endless) = endless;
}

UserData::UserData(std::string username, std::string password)
    : username(username), password(password)
{
    for (int i = 0; i < GameMode::GameModeCount; ++i) {
        highscore.at(i) = 0;
    }
}

UserData::UserData(const UserData &other)
    : username(other.getUsername()), password(other.getPassword()), highscore(other.getHighscore())
{
}

std::string UserData::getUsername() const
{
    return username;
}

std::string UserData::getPassword() const
{
    return password;
}

std::array<int, 4> UserData::getHighscore() const
{
    return highscore;
}

void UserData::setPassword(const std::string &newPassword)
{
    password = newPassword;
}

void UserData::setHighscore(int newHighscore, GameMode gameMode)
{
    highscore.at(gameMode) = newHighscore;
}

bool UserData::notAUser() const
{
    return (username == "") || (password == "");
}
