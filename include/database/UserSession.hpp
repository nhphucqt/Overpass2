#ifndef USER_SESSION_HPP
#define USER_SESSION_HPP

#include <UserRepo.hpp>
#include <UserData.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>

class UserSession
{
public:
    UserSession();
    ~UserSession();

    bool isLoggedin() const;
    std::string getUsername() const;
    std::string getPassword() const;
    void loginUser(const std::string &username, const std::string &password);
    void logoutUser();
    void loadLoginState(const std::string &filename);
    void saveLoginState(const std::string &filename);

private:
    UserData *currentUser;
    UserRepo &repo;
    bool isLogin;
};

#endif