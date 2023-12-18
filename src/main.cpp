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

#include <stdexcept>
#include <iostream>

int main() {
	try {
		Game game;
		game.run();
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}