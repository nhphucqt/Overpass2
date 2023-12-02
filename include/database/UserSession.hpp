#ifndef USER_SESSION_HPP
#define USER_SESSION_HPP

#include <UserRepo.hpp>
#include <UserData.hpp>
#include <stdexcept>
#include <iostream>

class UserSession
{
public:
    UserSession();
    ~UserSession();

    bool isLoggedin() const;
    std::string getUsername() const;
    void loginUser(const std::string &username, const std::string &password);
    void logoutUser();

private:
    UserData *currentUser;
    UserRepo &repo;
    bool isLogin;
};

#endif