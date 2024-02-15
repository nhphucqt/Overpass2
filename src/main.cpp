#include <Application.hpp>
#include <AppConfig.hpp>
#include <UtilitySave.hpp>
#include <ActivityID.hpp>

int main()
{
	unsigned int seed = std::time(nullptr);
	std::cerr << "Seed: " << seed << std::endl;
	std::srand(seed);

	AppConfig &config = AppConfig::getInstance();
	sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
	std::string windowTitle = config.get<std::string>(ConfigKey::AppName);


	std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
	std::error_code err;
    UtilitySave::CreateDirectoryRecursive(dataPath, err);

	Application app(windowSize.x, windowSize.y, windowTitle);
	app.addLauncher(ActivityID::MainMenu);
	app.run();

	return 0;
}