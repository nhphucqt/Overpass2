// #include <Application.hpp>
// #include <ActivityFactory.hpp>
// #include <MainMenuActivity.hpp>
// #include <AppConfig.hpp>
// #include <GameSetting.hpp>

// int main()
// {
//   AppConfig &config = AppConfig::getInstance();
//   sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
//   std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

//   // std::cout << windowTitle << std::endl;
//   // std::cout << windowSize.x << ' ' << windowSize.y << std::endl;

//   Application app(windowSize.x, windowSize.y, windowTitle);
//   Activity::Ptr launcher = std::make_unique<MainMenuActivity>();
//   app.addLauncher(std::move(launcher));
//   app.run();

//   GameSetting setting;
//   MusicPlayer::getInstance().setVolume(30);
//   SoundPlayer::getInstance().setVolume(20);

//   return 0;
// }

#include <Game.hpp>
#include <UserRepo.hpp>

#include <stdexcept>
#include <iostream>

int main() {
	UserRepo& repo = UserRepo::getInstance();
	// repo.addUser(UserData("pikachu", "123", 100, 200, 300, 400));
	UserData pikachu = repo.getUserByLogin("pikachu", "123");
	pikachu.setHighscore(500, UserData::GameMode::easy);
	repo.updateUser(pikachu);
	// repo.addUser(UserData("Raichu", "456", 800, 400, 200, 100));
	// repo.addUser(UserData("Charlizard", "789", 3000, 4000, 5000, 6000));
	// repo.addUser(UserData("Sqirtle", "1011", 100, 300, 200, 100));


	UserRepo::Leaderboard leaderboard = repo.getLeaderboard(UserData::GameMode::easy);
	for (int i = 0; i < leaderboard.size(); ++i)
	{
		std::cout << leaderboard.at(i).first << " " << leaderboard.at(i).second << std::endl;
	}

	// try {
	// 	Game game;
	// 	game.run();
	// }
	// catch (std::exception& e) {
	// 	std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	// }
}