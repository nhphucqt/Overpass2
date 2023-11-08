#include <Application.hpp>
#include <DemoActivity.hpp>
#include <AppConfig.hpp>
#include <ResourceManager.hpp>

int main()
{
  std::cout << AppConfig::getInstance().get<std::string>(ConfigKey::AppName) << std::endl;
  std::pair<int, int> windowSize = AppConfig::getInstance().get<std::pair<int, int>>(ConfigKey::WindowSize);
  std::cout << windowSize.first << ' ' << windowSize.second << std::endl;

  Application app(windowSize.first, windowSize.second, "Application");
  Activity::Ptr launcher = std::make_unique<DemoActivity>();
  app.addLauncher(std::move(launcher));
  app.run();
  return 0;
}