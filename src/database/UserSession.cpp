#include <UserSession.hpp>

UserSession::UserSession()
    : currentUser(nullptr), isLogin(false), repo(UserRepo::getInstance())
{
    loadLoginState("data/login.txt");
}

UserSession::~UserSession()
{
    saveLoginState("data/login.txt");

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
        throw std::invalid_argument("User not logged in.\n");

    return currentUser->getUsername();
}

std::string UserSession::getPassword() const
{
    if (!isLogin)
        throw std::invalid_argument("User not logged in.\n");

    return currentUser->getPassword();
}

void UserSession::loginUser(const std::string &username, const std::string &password)
{
    if (currentUser)
    {
        std::cerr << "An account has already logged in. Please log out first\n";
        return;
    }

    currentUser = new UserData(repo.getUserByLogin(username, password));

    if (currentUser->notAUser())
    {
        std::cerr << "incorrect username or password.\n";
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
        std::cerr << "User is not logged in!\n";
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

void UserSession::loadLoginState(const std::string &filename)
{
    std::ifstream inf{filename};
    if (!inf)
    {
        std::cerr << filename + " not found.\n";
        return;
    }

    std::string name;
    std::string pass;

    while (inf)
    {
        inf >> name >> pass;
        if (name != "" && pass != "")
        {
            loginUser(name, pass);
            return;
        }
    }

    inf.close();
}

void UserSession::saveLoginState(const std::string &filename)
{
    std::ofstream outf(filename, std::ofstream::out | std::ofstream::trunc);
    if (!currentUser)
    {
        std::cout << "User logged out, no login state to save.\n";
        return;
    }
    outf << currentUser->getUsername() << ' ' << currentUser->getPassword();
    std::cerr << "Login state saved.\n";
    outf.close();
}