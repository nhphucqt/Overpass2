#include <Application.hpp>
#include <ActivityFactory.hpp>
#include <MainMenuActivity.hpp>
#include <AppConfig.hpp>
#include <GameSetting.hpp>
#include <UserSession.hpp>
#include <UtilitySave.hpp>

int main(int argc, char *argv[])
{
	unsigned int seed = std::time(nullptr);
	std::cerr << "Seed: " << seed << std::endl;
	std::srand(seed);

	// Find the absolute path of the executable
	std::filesystem::path executablePath = std::filesystem::canonical(std::filesystem::path(argv[0]).parent_path());

	// Set the working directory to the executable's directory
	std::filesystem::current_path(executablePath);

	AppConfig &config = AppConfig::getInstance();
	sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
	std::string windowTitle = config.get<std::string>(ConfigKey::AppName);

	std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
	std::error_code err;
	UtilitySave::CreateDirectoryRecursive(dataPath, err);

	Application app(windowSize.x, windowSize.y, windowTitle);
	Activity::Ptr launcher = std::make_unique<MainMenuActivity>();
	app.addLauncher(std::move(launcher));
	app.run();

	return 0;
}