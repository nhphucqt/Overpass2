#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <MainMenuActivity.hpp>
#include <AppConfig.hpp>
#include <UserRepo.hpp>

int main()
{
  AppConfig &config = AppConfig::getInstance();
  sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
  std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

  std::cout << windowTitle << std::endl;
  std::cout << windowSize.x << ' ' << windowSize.y << std::endl;

  Application app(windowSize.x, windowSize.y, windowTitle);
  Activity::Ptr launcher = std::make_unique<MainMenuActivity>();
  app.addLauncher(std::move(launcher));
  app.run();

  // UserRepo &userRepo = UserRepo::getInstance();
  // // userRepo.addUser(UserData("john doe", "123", 2300));
  // // userRepo.addUser(UserData("Charmander", "asdf", 4600));
  // // userRepo.addUser(UserData("pikachu", "4567", 3200));
  // // userRepo.addUser(UserData("jinx", "9876", 1000));

  // // userRepo.deleteUser("john doe");
  // userRepo.updateUser(UserData("pikachu", "4325", 6000));

  // UserData John = userRepo.getUserByLogin("john doe", "123");
  // UserData pikachu = userRepo.getUserByLogin("pikachu", "4567");
  // std::cout << John.getUsername() << ' ' << John.getHighscore() << std::endl;
  // std::cout << pikachu.getUsername() << ' ' << pikachu.getHighscore() << std::endl;

  // UserRepo::Leaderboard leaderboard = userRepo.getLeaderboard();

  // std::cout << "Leaderboard:\n";
  // for (auto &user : leaderboard)
  // {
  //   std::cout << user.first << ' ' << user.second << std::endl;
  // }

  return 0;
}