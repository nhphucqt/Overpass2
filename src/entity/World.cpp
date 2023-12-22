#include <World.hpp>

World::World(sf::RenderWindow &window)
	: mWindow(window), mWorldView(window.getDefaultView()), mTextures(), mSceneGraph(), mSceneLayers(), mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y * 10), mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f), mScrollSpeed(-600.f), clock(), stop(false), playerLaneIndex(3), scrollDistance(0)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	if (stop)
		return;
	// Scroll the world
	scroll(dt);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
	{
		if (mPlayer->getState() == PlayerNode::State::Idle && clock.getElapsedTime().asSeconds() > 0.1)
		{
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);
			clock.restart();
		}
		else
			mCommandQueue.pop();
	}

	handleCollisions();
	// Apply movements
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue &World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{
	// lanes
	mTextures.load(TextureID::Road, "/res/textures/Lane/Road.png");
	mTextures.load(TextureID::River, "/res/textures/Lane/River.png");
	mTextures.load(TextureID::Rail, "/res/textures/Lane/Rail.png");
	mTextures.load(TextureID::Field, "/res/textures/Lane/Field.png");
	// vehicles
	mTextures.load(TextureID::Car, "/res/textures/Vehicle/Car.png");
	mTextures.load(TextureID::Ambulance, "/res/textures/Vehicle/Ambulance.png");
	mTextures.load(TextureID::Taxi, "/res/textures/Vehicle/Taxi.png");
	mTextures.load(TextureID::Police, "/res/textures/Vehicle/Police.png");
	// traffic light
	mTextures.load(TextureID::TrafficLight, "/res/textures/TrafficLight.png");
	// animals
	mTextures.load(TextureID::Bear, "/res/textures/Animal/Bear.png");
	mTextures.load(TextureID::Boar, "/res/textures/Animal/Boar.png");
	mTextures.load(TextureID::Bunny, "/res/textures/Animal/Bunny.png");
	mTextures.load(TextureID::Deer, "/res/textures/Animal/Deer.png");
	mTextures.load(TextureID::Fox, "/res/textures/Animal/Fox.png");
	mTextures.load(TextureID::Wolf, "/res/textures/Animal/Wolf.png");
	// log
	mTextures.load(TextureID::Wood, "/res/textures/Wood.png");
	// greens aka plants
	mTextures.load(TextureID::Tree, "/res/textures/Green/Tree.png");
	mTextures.load(TextureID::Bush, "/res/textures/Green/Bush.png");
	mTextures.load(TextureID::CircleBush, "/res/textures/Green/CircleBush.png");
	// train
	mTextures.load(TextureID::Train, "/res/textures/Train.png");
	// character animation panes
	mTextures.load(TextureID::CharacterUp, "/res/textures/Character/Cat-Up.png");
	mTextures.load(TextureID::CharacterDown, "/res/textures/Character/Cat-Down.png");
	mTextures.load(TextureID::CharacterLeft, "/res/textures/Character/Cat-Left.png");
	mTextures.load(TextureID::CharacterRight, "/res/textures/Character/Cat-Right.png");
	mTextures.load(TextureID::CharacterIdle, "/res/textures/Character/Cat-Idle.png");
	// game over banner
	mTextures.load(TextureID::GameOver, "/res/textures/Lane/GameOver.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		std::unique_ptr<ViewGroup> layer(new Entity());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachView(std::move(layer));
	}
	mSceneLayers[Background]->setReverse(true);

	srand(time(NULL));
	int laneTypeCount = Lane::Type::Count;
	for (int i = 0; i < 50; ++i)
	{
		int randLane = rand() % laneTypeCount;
		bool reverse = rand() % 2;
		std::unique_ptr<Lane> lane;
		switch (randLane)
		{
		case 0:
			lane.reset(new Road(&mTextures, reverse));
			break;
		case 1:
			lane.reset(new River(&mTextures, reverse));
			break;
		case 2:
			lane.reset(new Field(&mTextures, reverse));
			break;
		case 3:
			lane.reset(new Railway(&mTextures, mSceneLayers[Aboveground], reverse));
			break;
		default:
			lane.reset(new Road(&mTextures, reverse));
		}
		lanes.push_back(lane.get());
		lane->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - 128 * i);
		mSceneLayers[Background]->attachView(std::move(lane));
	}
	std::unique_ptr<PlayerNode> player(new PlayerNode(mTextures, lanes, 3)); // last argument must be consistent with playerLaneIndex
	mPlayer = player.get();
	mSceneLayers[Aboveground]->attachView(std::move(player));
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();

	bool isChanged = false;

	if (position.x <= viewBounds.left)
	{
		position.x = position.x + 1;
		velocity.x = 0;
		isChanged = true;
	}
	else if (position.x >= viewBounds.left + viewBounds.width - 72.f)
	{
		position.x = position.x - 1;
		velocity.x = 0;
		isChanged = true;
	}

	if (position.y <= viewBounds.top)
	{
		position.y = position.y + 1;
		velocity.y = 0;
		isChanged = true;
	}
	else if (position.y >= viewBounds.top + viewBounds.height - 90.f)
	{
		// position.y = position.y - 1;
		// velocity.y = 0;
		// isChanged = true;
		gameOver();
	}

	if (isChanged)
	{
		mPlayer->move(velocity);
		mPlayer->setPosition(position);
	}
}

bool World::matchesCategories(ViewGroup::Pair &colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::handleCollisions()
{
	std::set<ViewGroup::Pair> collisionPairs;
	mPlayer->checkSceneCollision(*lanes[mPlayer->getCurrentLane()], collisionPairs);
	if (lanes.size() > mPlayer->getCurrentLane() + 1)
		mPlayer->checkSceneCollision(*lanes[mPlayer->getCurrentLane() + 1], collisionPairs);
	mPlayer->checkSceneCollision(*lanes[mPlayer->getCurrentLane() - 1], collisionPairs);

	bool onRiver = false;
	for (ViewGroup::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, Category::Player, Category::Lane))
			onRiver = false;
		else if (matchesCategories(pair, Category::Player, Category::Vehicle))
			gameOver();
		else if (matchesCategories(pair, Category::Player, Category::Animal))
			gameOver();
		else if (matchesCategories(pair, Category::Player, Category::Train))
			gameOver();
		else if (matchesCategories(pair, Category::Player, Category::Log))
		{
			onRiver = false;
			if (mPlayer->getState() == PlayerNode::Idle)
			{
				auto &log = static_cast<Log &>(*pair.second);
				mPlayer->setVelocity(log.getVelocity());
			}
			break;
		}
		else if (matchesCategories(pair, Category::Player, Category::River))
		{
			onRiver = true;
		}
		else if (matchesCategories(pair, Category::Player, Category::Green))
		{
			mPlayer->moveBack();
		}
	}

	if (onRiver)
		gameOver();
}

void World::scroll(sf::Time dt)
{
	int currentLaneIndex = mPlayer->getCurrentLane();
	if (currentLaneIndex > playerLaneIndex)
	{
		scrollDistance += 128.f;
		++playerLaneIndex;
	}
	else if (currentLaneIndex < playerLaneIndex)
	{
		scrollDistance -= 128.f;
		--playerLaneIndex;
	}

	float scrollStep = mScrollSpeed * dt.asSeconds();

	if (scrollDistance > 0)
	{
		scrollDistance += scrollStep;
		mWorldView.move(0.f, scrollStep);
	}
	// view gradually move up regardless of player's movement
	// else {
	// 	float step = -24.f * dt.asSeconds();
	// 	scrollDistance += step;
	// 	mWorldView.move(0, step);
	// }
}

void World::gameOver()
{
	std::unique_ptr<Entity> banner(new Entity(mTextures.get(TextureID::GameOver)));
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	banner->setPosition(viewBounds.getPosition().x, viewBounds.getPosition().y + 300);
	mSceneLayers[Aboveground]->attachView(std::move(banner));
	stop = true;
}
