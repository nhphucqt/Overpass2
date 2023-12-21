#include <UserData.hpp>

UserData::UserData(std::string username, std::string password, int highscore)
    : username(username), password(password), highscore(highscore)
{
}

UserData::UserData(std::string username, std::string password)
    : username(username), password(password), highscore(0)
{
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

int UserData::getHighscore() const
{
    return highscore;
}

void UserData::setPassword(const std::string &newPassword)
{
    password = newPassword;
}

void UserData::setHighscore(int newHighscore)
{
    highscore = newHighscore;
}

bool UserData::notAUser() const
{
    return (username == "") || (password == "") || (highscore < 0);
}
