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

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <array>
#include <queue>
#include <cmath>

// Forward declaration
namespace sf {
	class RenderWindow;
}

class World : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow &window);
	void update(sf::Time dt);
	void draw();
	CommandQueue &getCommandQueue();

private:
	void loadTextures();
	void buildScene();
	void adaptPlayerPosition();

private:
	enum Layer {
		Background,
		Aboveground,
		LayerCount
	};

private:
	sf::RenderWindow &mWindow;
	sf::View mWorldView;
	TextureManager mTextures;

	Entity mSceneGraph;
	std::array<ViewGroup *, LayerCount> mSceneLayers;
	CommandQueue mCommandQueue;
	PlayerNode *mPlayer;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	sf::Clock clock;
};

#endif
