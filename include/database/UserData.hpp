#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <string>
#include <array>

class UserData
{
public:
    enum GameMode {easy = 0, medium, hard, endless, GameModeCount};

public:
    UserData(std::string username, std::string password, int easy, int medium, int hard, int endless);
    UserData(std::string username, std::string password);
    UserData(const UserData &other);

    std::string getUsername() const;
    std::string getPassword() const;
    std::array<int, 4> getHighscore() const;

    void setPassword(const std::string &newPassword);
    void setHighscore(int newHighscore, GameMode gameMode);
    bool notAUser() const;

private:
    std::string username;
    std::string password;
    std::array<int, GameMode::GameModeCount> highscore;
};

#endif