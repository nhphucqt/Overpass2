#ifndef USER_REPO_HPP
#define USER_REPO_HPP

#include <UserData.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>

class UserRepo
{
public:
    typedef std::vector<std::pair<std::string, int>> Leaderboard;

public:
    static UserRepo &getInstance();
    UserRepo(const UserRepo &) = delete;
    UserRepo &operator=(const UserRepo &) = delete;
    SQLite::Database &getDatabase();

    UserData getUserByLogin(const std::string &username, const std::string &password) const;
    bool checkUser(const std::string &username, const std::string &password) const;
    Leaderboard getLeaderboard(UserData::GameMode gameMode) const;
    void addUser(const UserData &user);
    void updateUser(const UserData &user);
    void deleteUser(const std::string &username);
    bool userExist(const std::string &username);

private:
    SQLite::Database db;
    UserRepo();
};

#endif