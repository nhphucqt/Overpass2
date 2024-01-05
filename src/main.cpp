#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <MainMenuActivity.hpp>
#include <AppConfig.hpp>
#include <GameSetting.hpp>

int main()
{
  unsigned int seed = std::time(nullptr);
  // seed = 1704450765;
  std::cerr << "Seed: " << seed << std::endl;
  std::srand(seed);
  AppConfig &config = AppConfig::getInstance();
  sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
  std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

  Application app(windowSize.x, windowSize.y, windowTitle);
  Activity::Ptr launcher = std::make_unique<MainMenuActivity>();
  app.addLauncher(std::move(launcher));
  app.run();

  return 0;
}