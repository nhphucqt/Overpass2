#include "UserRepo.hpp"

UserRepo::UserRepo()
    : db("data/users.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    // db.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT, highscore INTEGER);");
    db.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT);");
    db.exec("CREATE TABLE IF NOT EXISTS highscores (username TEXT PRIMARY KEY, easy INTEGER, medium INTEGER, hard INTEGER, endless INTEGER);");
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
    SQLite::Statement userQuery(db, "SELECT * FROM users WHERE username = ? AND password = ?;");
    userQuery.bind(1, username);
    userQuery.bind(2, password);

    SQLite::Statement scoreQuery(db, "SELECT * FROM highscores WHERE username = ?;");
    scoreQuery.bind(1, username);

    if (userQuery.executeStep() && scoreQuery.executeStep())
        return UserData(userQuery.getColumn(0), userQuery.getColumn(1), scoreQuery.getColumn(1), scoreQuery.getColumn(2), scoreQuery.getColumn(3), scoreQuery.getColumn(4));

    return UserData("", "");
}

bool UserRepo::checkUser(const std::string &username, const std::string &password) const
{
    UserData user = getUserByLogin(username, password);
    return !user.notAUser();
}

UserRepo::Leaderboard UserRepo::getLeaderboard(UserData::GameMode gameMode) const
{
    std::string GameModeQuery;
    switch (gameMode)
    {
    case UserData::GameMode::easy:
        GameModeQuery = "easy";
        break;
    case UserData::GameMode::medium:
        GameModeQuery = "medium";
        break;
    case UserData::GameMode::hard:
        GameModeQuery = "hard";
        break;
    case UserData::GameMode::endless:
        GameModeQuery = "endless";
        break;
    default:
        throw std::runtime_error("REPO ERR: Unknown Game mode.\n");
    }

    UserRepo::Leaderboard leaderboard;
    SQLite::Statement scoreQuery(db, "SELECT * FROM highscores ORDER BY " + GameModeQuery + " DESC LIMIT 20;");
    while (scoreQuery.executeStep())
    {
        std::pair<std::string, int> userScore(scoreQuery.getColumn(0), scoreQuery.getColumn(static_cast<int>(gameMode) + 1));
        leaderboard.emplace_back(userScore);
    }
    return leaderboard;
}

void UserRepo::addUser(const UserData &user)
{
    if (user.notAUser())
        throw std::runtime_error("REPO ERR: Updating not a user");

    SQLite::Statement userQuery(db, "INSERT INTO users (username, password) VALUES (?, ?);");
    userQuery.bind(1, user.getUsername());
    userQuery.bind(2, user.getPassword());

    SQLite::Statement scoreQuery(db, "INSERT INTO highscores (username, easy, medium, hard, endless) VALUES (?, ?, ?, ?, ?);");
    scoreQuery.bind(1, user.getUsername());
    scoreQuery.bind(2, user.getHighscore().at(UserData::GameMode::easy));
    scoreQuery.bind(3, user.getHighscore().at(UserData::GameMode::medium));
    scoreQuery.bind(4, user.getHighscore().at(UserData::GameMode::hard));
    scoreQuery.bind(5, user.getHighscore().at(UserData::GameMode::endless));

    userQuery.exec();
    scoreQuery.exec();
}

void UserRepo::updateUser(const UserData &user)
{
    if (user.notAUser())
        throw std::runtime_error("REPO ERR: Updating not a user");

    if (!userExist(user.getUsername()))
        throw std::runtime_error("User with username " + user.getUsername() + " not found.");

    SQLite::Statement userQuery(db, "UPDATE users SET password = ? WHERE username = ?;");
    userQuery.bind(1, user.getPassword());
    userQuery.bind(2, user.getUsername());

    SQLite::Statement scoreQuery(db, "UPDATE highscores SET easy = ?, medium = ?, hard = ?, endless = ? WHERE username = ?;");
    scoreQuery.bind(1, user.getHighscore().at(UserData::GameMode::easy));
    scoreQuery.bind(2, user.getHighscore().at(UserData::GameMode::medium));
    scoreQuery.bind(3, user.getHighscore().at(UserData::GameMode::hard));
    scoreQuery.bind(4, user.getHighscore().at(UserData::GameMode::endless));
    scoreQuery.bind(5, user.getUsername());

    userQuery.exec();
    scoreQuery.exec();
}

void UserRepo::deleteUser(const std::string &username)
{
    if (!userExist(username))
        throw std::runtime_error("REPO ERR: User with username " + username + " not found.");

    SQLite::Statement userQuery(db, "DELETE FROM users WHERE username = ?;");
    userQuery.bind(1, username);

    SQLite::Statement scoreQuery(db, "DELETE FROM highscores WHERE username = ?;");
    scoreQuery.bind(1, username);

    userQuery.exec();
}

bool UserRepo::userExist(const std::string &username)
{
    SQLite::Statement query(db, "SELECT EXISTS(SELECT 1 FROM users WHERE username = ? LIMIT 1);");
    query.bind(1, username);

    if (query.executeStep())
        return query.getColumn(0).getInt() > 0;

    return false;
}
