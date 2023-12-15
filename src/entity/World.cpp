#include <World.hpp>



World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt) {
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());	
	mPlayer->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	adaptPlayerVelocity();

	// Move the player sidewards (plane scouts follow the main aircraft)
	sf::Vector2f position = mPlayer->getPosition();
	sf::Vector2f velocity = mPlayer->getVelocity();

	// // If player touches borders, flip its X velocity
	if (position.x <= mWorldBounds.left + 150.f
	 || position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayer->setVelocity(velocity);
	}

	// Apply movements
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw() {
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
	return mCommandQueue;
}

void World::loadTextures() {
	mTextures.load(TextureID::Road, "../../res/textures/Road.png");
	mTextures.load(TextureID::River, "../../res/textures/River.png");
    mTextures.load(TextureID::Rail, "../../res/textures/Rail.png");
    mTextures.load(TextureID::Field, "../../res/textures/Field.png");
	mTextures.load(TextureID::Player, "../../res/textures/Player.png");
    mTextures.load(TextureID::Car, "../../res/textures/Car.png");
    mTextures.load(TextureID::Ambulance, "../../res/textures/Ambulance.png");
    mTextures.load(TextureID::Taxi, "../../res/textures/Taxi.png");
    mTextures.load(TextureID::Police, "../../res/textures/Police.png");
	mTextures.load(TextureID::TrafficLight, "../../res/textures/TrafficLight.png");
	mTextures.load(TextureID::Fox, "../../res/textures/Fox.png");
    mTextures.load(TextureID::Wood, "../../res/textures/Wood.png");
    mTextures.load(TextureID::Tree, "../../res/textures/Tree.png");
    mTextures.load(TextureID::Bush, "../../res/textures/Bush.png");
    mTextures.load(TextureID::CircleBush, "../../res/textures/CircleBush.png");
    mTextures.load(TextureID::Train, "../../res/textures/Train.png");
    // mTextures.load(TextureID::Crocodile, "../../res/textures/Crocodile.png");
}

void World::buildScene() {
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i) {
		std::unique_ptr<ViewGroup> layer(new Entity());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachView(std::move(layer));
	}
	mSceneLayers[Background]->setReverse(true);

	srand(time(NULL));
	int laneTypeCount = Lane::Type::Count;
	for (int i = 0; i < 50; ++i) {
    	int randLane = rand() % laneTypeCount;
    	bool reverse = rand() % 2;
		std::unique_ptr<Lane> lane;
		switch (randLane) {
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
			lane.reset(new Railway(&mTextures, mSceneLayers[Aboveground],reverse));
			break;
		default:
			lane.reset(new Road(&mTextures, reverse));
		}
		lane->setPosition(mWorldBounds.left, mWorldBounds.top + mWorldBounds.height - 128*i);
		mSceneLayers[Background]->attachView(std::move(lane));
	}
	std::unique_ptr<PlayerNode> player(new PlayerNode(mTextures));
	player->setPosition(mSpawnPosition);
	mPlayer = player.get();
	mSceneLayers[Aboveground]->attachView(std::move(player));

}

void World::adaptPlayerPosition() {
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayer->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayer->setPosition(position);
}

void World::adaptPlayerVelocity() {
	sf::Vector2f velocity = mPlayer->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayer->setVelocity(velocity / std::sqrt(2.f));
}
