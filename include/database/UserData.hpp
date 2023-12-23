#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <string>

class UserData
{
public:
    UserData(std::string username, std::string password, int highscore);
    UserData(std::string username, std::string password);
    UserData(const UserData &other);

    std::string getUsername() const;
    std::string getPassword() const;
    int getHighscore() const;

    void setPassword(const std::string &newPassword);
    void setHighscore(int newHighscore);
    bool notAUser() const;

private:
    std::string username;
    std::string password;
    int highscore;
};

#endif