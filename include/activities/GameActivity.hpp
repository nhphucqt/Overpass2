#ifndef GAME_ACTIVITY_HPP
#define GAME_ACTIVITY_HPP

#include <Activity.hpp>
#include <Command.hpp>
#include <CommandQueue.hpp>
#include <Field.hpp>
#include <Green.hpp>
#include <Log.hpp>
#include <PlayerNode.hpp>
#include <Railway.hpp>
#include <ResourceID.hpp>
#include <ResourceManager.hpp>
#include <River.hpp>
#include <Road.hpp>
#include <Train.hpp>
#include <ViewGroup.hpp>
#include <Player.hpp>

#include <array>
#include <list>

class GameActivity : public Activity {
public:
    static const int ACTION_NEW_GAME = 1;
    static const int ACTION_CONTINUE_GAME = 2;

    enum class GameLevel {
        Easy,
        Medium,
        Hard,
        Endless
    };

private:
	enum Layer {
		Background,
		Aboveground,
		LayerCount
	};

private:
	Player mPlayer;

    FontManager mFontManager;
	TextureManager mTextures;
    bool stop;
	std::list<Lane*> lanes;

	std::array<ViewGroup *, LayerCount> mSceneLayers;
	CommandQueue mCommandQueue;
	PlayerNode *mPlayerNode;

	sf::View mWorldView;
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	sf::Clock clock;
	int playerLaneIndex;
	int scrollDistance;
	int actualScrollDistance;

public:
	CommandQueue &getCommandQueue();

protected:
    virtual void onEvent(const sf::Event& event) override;
	virtual void onEventProcessing() override;
    virtual void onCreate() override;
    virtual void onLoadResources() override;
    virtual void onAttach() override;
    virtual void onResume() override;
    virtual void onPause() override;
    virtual void onDestroy() override;
    void updateCurrent(sf::Time dt) override;
    virtual void onActivityResult(int requestCode, int resultCode, Intent::Ptr data) override;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void adaptPlayerPosition();
	bool matchesCategories(ViewGroup::Pair& colliders, Category::Type type1, Category::Type type2);
	void handleCollisions();
	void scroll(sf::Time dt);
	void gameOver();
};

#endif 