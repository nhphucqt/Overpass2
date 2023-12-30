#include <UserSession.hpp>
#include <cassert>

const char *UserSession::loginStateFilename = "data/login.txt";

UserSession &UserSession::getInstance()
{
    static UserSession instance;
    return instance;
}

UserSession::UserSession()
    : isLogin(false), repo(UserRepo::getInstance())
{
    loadLoginState("data/login.txt");
}

UserSession::~UserSession()
{
    saveLoginState("data/login.txt");
    if (currentUser)
    {
        repo.updateUser(*currentUser);
        delete currentUser;
    }
}

bool UserSession::isLoggedin() const
{
    return isLogin;
}

void UserSession::loginUser(const std::string &username, const std::string &password)
{
    if (isLogin)
    {
        throw std::runtime_error("An account has already logged in. Please log out first\n");
    }

    currentUser = repo.getUserByLogin(username, password);

    if (currentUser.notAUser())
    {
        throw std::runtime_error("incorrect username or password.\n");
    }

    isLogin = true;
    std::cout << username << " logged in.\n";

    saveLoginState(loginStateFilename);
}

void UserSession::logoutUser()
{
    if (!isLoggedin())
    {
        std::cerr << "User is not logged in!\n";
        return;
    }

    assert(!currentUser.notAUser());

    std::cout << currentUser.getUsername() << " logged out.\n";

    isLogin = false;
    currentUser = UserData();

    saveLoginState(loginStateFilename);
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
    outf << currentUser.getUsername() << ' ' << currentUser.getPassword();
    std::cerr << "Login state saved.\n";
    outf.close();
}

UserData &UserSession::getCurrentUser()
{
    return currentUser;
}