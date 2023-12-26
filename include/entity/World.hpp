#ifndef WORLD_HPP
#define WORLD_HPP

#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <ViewGroup.hpp>
#include <Log.hpp>
#include <Green.hpp>
#include <Train.hpp>
#include <River.hpp>
#include <Road.hpp>
#include <Field.hpp>
#include <Railway.hpp>
#include <PlayerNode.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>
#include <UserSession.hpp>
#include <UtilitySave.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <array>
#include <queue>
#include <cmath>

// Forward declaration
namespace sf
{
	class RenderWindow;
}

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow &window, bool isLoad = false);
	void update(sf::Time dt);
	void draw();
	CommandQueue &getCommandQueue();

private:
	void loadTextures();
	void buildScene();
	void loadScene(const std::string &filename);
	void saveScene(const std::string &filename);
	void adaptPlayerPosition();
	bool matchesCategories(ViewGroup::Pair &colliders, Category::Type type1, Category::Type type2);

	void handleCollisions();
	void scroll(sf::Time dt);
	void gameOver();

private:
	enum Layer
	{
		Background,
		Aboveground,
		LayerCount
	};

private:
	bool stop;
	sf::RenderWindow &mWindow;
	sf::View mWorldView;
	TextureManager mTextures;
	std::vector<Lane *> lanes;

	Entity mSceneGraph;
	std::array<ViewGroup *, LayerCount> mSceneLayers;
	CommandQueue mCommandQueue;
	PlayerNode *mPlayer;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	sf::Clock clock;
	int playerLaneIndex;
	int scrollDistance;
	int actualScrollDistance;

public:
	void saveGameState(const std::string &filepath);
	void loadGameState(const std::string &filepath);
};

#endif
