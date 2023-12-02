#include <UserSession.hpp>

UserSession::UserSession()
    : currentUser(nullptr), isLogin(false), repo(UserRepo::getInstance())
{
}

UserSession::~UserSession()
{
    if (currentUser)
        delete currentUser;
}

bool UserSession::isLoggedin() const
{
    return isLogin;
}

std::string UserSession::getUsername() const
{
    if (!isLogin)
        throw std::invalid_argument("User not logged in.");

    return currentUser->getUsername();
}

void UserSession::loginUser(const std::string &username, const std::string &password)
{
    currentUser = new UserData(repo.getUserByLogin(username, password));

    if (currentUser->notAUser())
    {
        std::cerr << "username or password is incorrect.";
        delete currentUser;
        return;
    }

    isLogin = true;
    std::cout << username << " logged in.\n";
}

void UserSession::logoutUser()
{
    if (!isLogin)
    {
        std::cerr << "User is not logged in!";
        return;
    }

    if (currentUser)
    {
        std::cout << currentUser->getUsername() << " logged out.\n";
        delete currentUser;
        currentUser = nullptr;
    }
    isLogin = false;
}