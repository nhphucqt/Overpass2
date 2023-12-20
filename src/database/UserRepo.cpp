#include "UserRepo.hpp"

UserRepo::UserRepo()
    : db("data/users.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    db.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, highscore INTEGER);");
}

UserRepo &UserRepo::getInstance()
{
    static UserRepo instance;
    return instance;
}

SQLite::Database &UserRepo::getDatabase()
{
    return db;
}

UserData UserRepo::getUserByLogin(const std::string &username, const std::string &password) const
{
    SQLite::Statement query(db, "SELECT * FROM users WHERE username = ? AND password = ?;");
    query.bind(1, username);
    query.bind(2, password);

    if (query.executeStep())
        return UserData(query.getColumn(0), query.getColumn(1), query.getColumn(2));

    return UserData("", "", -1);
}

UserRepo::Leaderboard UserRepo::getLeaderboard() const
{
    UserRepo::Leaderboard leaderboard;
    SQLite::Statement query(db, "SELECT * FROM users ORDER BY highscore DESC LIMIT 20;");
    while (query.executeStep())
    {
        std::pair<std::string, int> userScore(query.getColumn(0), query.getColumn(2));
        leaderboard.emplace_back(userScore);
    }
    return leaderboard;
}

void UserRepo::addUser(const UserData &user)
{
    if (user.notAUser())
        throw std::runtime_error("Updating not a user");

    SQLite::Statement query(db, "INSERT INTO users (username, password, highscore) VALUES (?, ?, ?);");
    query.bind(1, user.getUsername());
    query.bind(2, user.getPassword());
    query.bind(3, user.getHighscore());

    query.exec();
}

void UserRepo::updateUser(const UserData &user)
{
    if (user.notAUser())
        throw std::runtime_error("Updating not a user");

    if (!userExist(user.getUsername()))
        throw std::runtime_error("User with username " + user.getUsername() + " not found.");

    SQLite::Statement query(db, "UPDATE users SET password = ?, highscore = ? WHERE username = ?;");
    query.bind(1, user.getPassword());
    query.bind(2, user.getHighscore());
    query.bind(3, user.getUsername());

    query.exec();
}

void UserRepo::deleteUser(const std::string &username)
{
    if (!userExist(username))
        throw std::runtime_error("User with username " + username + " not found.");

    SQLite::Statement query(db, "DELETE FROM users WHERE username = ?;");
    query.bind(1, username);
    query.exec();
}

bool UserRepo::userExist(const std::string &username)
{
    SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM users WHERE username = ? LIMIT 1);");
    query.bind(1, username);

    if (query.executeStep())
        return query.getColumn(0).getInt() > 0;

    return false;
}
