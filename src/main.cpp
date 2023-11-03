#include "ResourceID.hpp"
#include "SoundPlayer.hpp"
#include <Application.hpp>
#include <DemoActivity.hpp>
#include <MusicPlayer.hpp>

int main()
{
  Application app(800, 600, "Application");
  Activity::Ptr launcher = std::make_unique<DemoActivity>();
  app.addLauncher(std::move(launcher));
  app.run();
  return 0;
}