#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <MainMenuActivity.hpp>
#include <AppConfig.hpp>
#include <GameSetting.hpp>
#include <UserSession.hpp>

int main()
{
	// UserRepo::getInstance().addUser(UserData("pikachu", "123"));
	UserSession& userSession = UserSession::getInstance();
	// userSession.loginUser("pikachu", "123");

	AppConfig &config = AppConfig::getInstance();
	sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
	std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

	Application app(windowSize.x, windowSize.y, windowTitle);
	Activity::Ptr launcher = std::make_unique<MainMenuActivity>();
	app.addLauncher(std::move(launcher));
	app.run();

	return 0;
}