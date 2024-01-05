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
    static UserSession &getInstance();
    UserSession &operator=(const UserSession &) = delete;
    UserSession(const UserSession &) = delete;

    ~UserSession();

    UserData &getCurrentUser();

    bool isLoggedin() const;

    void loginUser(const std::string &username, const std::string &password);
    void logoutUser();

private:
    void loadLoginState(const std::string &filename);
    void saveLoginState(const std::string &filename);

private:
    UserSession();
    UserData *currentUser;
    UserRepo &repo;
    bool isLogin;

    UserSession();

    static const char *loginStateFilename;
};

#endif