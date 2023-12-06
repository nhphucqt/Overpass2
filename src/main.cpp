#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <MainMenuActivity.hpp>
#include <AppConfig.hpp>
#include <UserSession.hpp>

int main()
{
  // AppConfig &config = AppConfig::getInstance();
  // sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
  // std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

  // std::cout << windowTitle << std::endl;
  // std::cout << windowSize.x << ' ' << windowSize.y << std::endl;

  Application app(windowSize.x, windowSize.y, windowTitle);
  Activity::Ptr launcher = std::make_unique<MainMenuActivity>();
  app.addLauncher(std::move(launcher));
  app.run();

//   UserSession session;
  // if (!session.isLoggedin())
  // {
//   session.loginUser("pikachu", "4567");
  // session.logoutUser();
  // }
  // session.loginUser("jinx", "9876");
  // session.logoutUser();

  return 0;
}