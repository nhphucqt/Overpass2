#ifndef USER_DATA_HPP
#define USER_DATA_HPP

#include <string>

class UserData
{
public:
    UserData(std::string username, std::string password, int highscore);
    UserData(const UserData &other);

    std::string getUsername() const;
    std::string getPassword() const;
    int getHighscore() const;

    void setHighscore(int highscore);
    bool notAUser() const;

private:
    std::string username;
    std::string password;
    int highscore;
};

#endif