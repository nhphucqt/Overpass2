#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <DemoActivity.hpp>
#include <AppConfig.hpp>
#include <ResourceManager.hpp>

int main()
{
  AppConfig& config = AppConfig::getInstance();
  std::pair<int, int> windowSize = config.get<std::pair<int, int>>(ConfigKey::WindowSize);
  std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

  std::cout << windowTitle << std::endl;
  std::cout << windowSize.first << ' ' << windowSize.second << std::endl;

  Application app(windowSize.first, windowSize.second, windowTitle);
  Activity::Ptr launcher = std::make_unique<DemoActivity>();
  app.addLauncher(std::move(launcher));
  app.run();
  return 0;
}