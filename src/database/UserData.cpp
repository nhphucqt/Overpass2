#include <UserData.hpp>

const char* UserData::gameModeNames[(int)GameMode::GameModeCount] = {"Easy", "Medium", "Hard", "Insane", "Rain Day", "Endless"};

UserData::UserData()
    : username(""), password("")
{
    for (int i = 0; i < (int)GameMode::GameModeCount; ++i) {
        highscore.at(i) = 0;
    }
}

UserData::UserData(std::string username, std::string password, int easy, int medium, int hard, int insane, int rainday, int endless)
    : username(username), password(password)
{
    highscore.at((int)GameMode::easy) = easy;
    highscore.at((int)GameMode::medium) = medium;
    highscore.at((int)GameMode::hard) = hard;
    highscore.at((int)GameMode::insane) = insane;
    highscore.at((int)GameMode::rainday) = rainday;
    highscore.at((int)GameMode::endless) = endless;
}

UserData::UserData(std::string username, std::string password)
    : username(username), password(password)
{
    for (int i = 0; i < (int)GameMode::GameModeCount; ++i) {
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

std::array<int, (int)UserData::GameMode::GameModeCount> UserData::getHighscore() const
{
    return highscore;
}

int UserData::getHighscore(GameMode mode) const
{
    return highscore.at((int)mode);
}

void UserData::setPassword(const std::string &newPassword)
{
    password = newPassword;
}

void UserData::setHighscore(int newHighscore, GameMode gameMode)
{
    highscore.at((int)gameMode) = newHighscore;
}

void UserData::updateHighscore(int newHighscore, GameMode gameMode)
{
    if (newHighscore > highscore.at((int)gameMode)) {
        highscore.at((int)gameMode) = newHighscore;
    }
}

bool UserData::notAUser() const
{
    return (username == "") || (password == "");
}
