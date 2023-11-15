#include <UserData.hpp>

UserData::UserData(std::string username, std::string password, int highscore)
    : username(username), password(password), highscore(highscore)
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

void UserData::setHighscore(int highscore)
{
    this->highscore = highscore;
}

bool UserData::notAUser() const
{
    return username == "" || password == "" || highscore < 0;
}
