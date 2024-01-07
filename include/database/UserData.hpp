#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <string>
#include <array>

class UserData
{
public:
    enum GameMode {easy = 0, medium, hard, insane, rainday, endless, GameModeCount};
    static const char* gameModeNames[GameMode::GameModeCount];

public:
    UserData();
    UserData(std::string username, std::string password, int easy, int medium, int hard, int insane, int rainday, int endless);
    UserData(std::string username, std::string password);
    UserData(const UserData &other);

    std::string getUsername() const;
    std::string getPassword() const;
    std::array<int, GameMode::GameModeCount> getHighscore() const;
    int getHighscore(GameMode mode) const;

    void setPassword(const std::string &newPassword);
    void setHighscore(int newHighscore, GameMode gameMode);
    void updateHighscore(int newHighscore, GameMode gameMode);
    bool notAUser() const;

private:
    std::string username;
    std::string password;
    std::array<int, GameMode::GameModeCount> highscore;
};

#endif