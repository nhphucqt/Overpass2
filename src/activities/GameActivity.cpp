#include <ActivityFactory.hpp>
#include <AppConfig.hpp>
#include <ButtonView.hpp>
#include <Field.hpp>
#include <GameActivity.hpp>
#include <SettingsActivity.hpp>
#include <Railway.hpp>
#include <River.hpp>
#include <Road.hpp>
#include <iterator>
#include <UserSession.hpp>
#include <UtilitySave.hpp>

#include <LayerView.hpp>
#include <ButtonView.hpp>
#include <SpriteButtonView.hpp>
#include <TextView.hpp>
#include <IconButtonFactory.hpp>

#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

const std::string GameActivity::EXTRA_GAME_LEVEL = "level";
const std::string GameActivity::EXTRA_NUM_PLAYERS = "num_players";

const std::string GameActivity::GAME_STATE_FILENAME = "save.data";
const std::string GameActivity::PLAYER_STATE_FILENAME = "player.data";

#include <LayerView.hpp>
#include <RainLayer.hpp>

#include <ButtonView.hpp>
#include <SpriteButtonView.hpp>
#include <TextView.hpp>
#include <IconButtonFactory.hpp>

void GameActivity::onLoadResources()
{
    // lanes
    mTextures.load(TextureID::Road, "res/textures/Lane/Road.png");
    mTextures.load(TextureID::River, "res/textures/Lane/River.png");
    mTextures.load(TextureID::Rail, "res/textures/Lane/Rail.png");
    mTextures.load(TextureID::Field, "res/textures/Lane/Field.png");
    // vehicles
    mTextures.load(TextureID::Car, "res/textures/Vehicle/Car.png");
    mTextures.load(TextureID::Ambulance, "res/textures/Vehicle/Ambulance.png");
    mTextures.load(TextureID::Taxi, "res/textures/Vehicle/Taxi.png");
    mTextures.load(TextureID::Police, "res/textures/Vehicle/Police.png");
    mTextures.load(TextureID::Supercar, "res/textures/Vehicle/Supercar.png");
    // traffic light
    mTextures.load(TextureID::TrafficLight, "res/textures/TrafficLight.png");
    mTextures.load(TextureID::RailwayLightOff, "res/textures/RailwayLightOff.png");
    mTextures.load(TextureID::RailwayLightOn, "res/textures/RailwayLightOn.png");
    // animals
    mTextures.load(TextureID::Bear, "res/textures/Animal/Bear.png");
    mTextures.load(TextureID::Boar, "res/textures/Animal/Boar.png");
    mTextures.load(TextureID::Bunny, "res/textures/Animal/Bunny.png");
    mTextures.load(TextureID::Deer, "res/textures/Animal/Deer.png");
    mTextures.load(TextureID::Fox, "res/textures/Animal/Fox.png");
    mTextures.load(TextureID::Wolf, "res/textures/Animal/Wolf.png");
    // log
    mTextures.load(TextureID::WoodL2, "res/textures/WoodL2.png");
    mTextures.load(TextureID::WoodL3, "res/textures/WoodL3.png");
    // greens aka plants
    mTextures.load(TextureID::Tree, "res/textures/Green/Tree.png");
    mTextures.load(TextureID::Bush, "res/textures/Green/Bush.png");
    mTextures.load(TextureID::CircleBush, "res/textures/Green/CircleBush.png");
    // train
    mTextures.load(TextureID::Train, "res/textures/Train.png");
    // character animation panes
    mTextures.load(TextureID::CharacterUp, "res/textures/Character/Cat-Up.png");
    mTextures.load(TextureID::CharacterDown,
                   "res/textures/Character/Cat-Down.png");
    mTextures.load(TextureID::CharacterLeft,
                   "res/textures/Character/Cat-Left.png");
    mTextures.load(TextureID::CharacterRight,
                   "res/textures/Character/Cat-Right.png");
    mTextures.load(TextureID::CharacterIdle,
                   "res/textures/Character/Cat-Idle.png");
    // game over banner
    mTextures.load(TextureID::homeButtonsTexture, "res/textures/ui/buttons/home_button.png");
    mTextures.load(TextureID::pauseButtonsTexture, "res/textures/ui/buttons/pause_button.png");
    mTextures.load(TextureID::continueButtonsTexture, "res/textures/ui/buttons/continue_button.png");
    mTextures.load(TextureID::settingButtonsTexture, "res/textures/ui/buttons/setting_button.png");
    mTextures.load(TextureID::replayButtonsTexture, "res/textures/ui/buttons/replay_button.png");
    mTextures.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");

    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
}

void GameActivity::onCreate() {
    Intent* intent = getIntent();
    assert(intent->hasExtra(EXTRA_NUM_PLAYERS));

    MusicPlayer::getInstance().setVolume(50.f);
}

void GameActivity::onAttach()
{
    sf::RenderWindow &window = getActivityManager()->getWindow();
    window.setKeyRepeatEnabled(false);
    mWorldView = window.getDefaultView();

    mIsGameOver = false;
    mScrollSpeed = -600.f;

    effectLayer = std::make_unique<LayerView>();
    statusLayer = std::make_unique<LayerView>();

    createStatusLayer();
    createEffectLayer();

    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        std::unique_ptr<ViewGroup> layer(new Entity());
        mSceneLayers[i] = layer.get();

        attachView(std::move(layer));
    }
    mSceneLayers[Background]->setReverse(true);

    if (getIntent()->getAction() == ACTION_NEW_GAME) {
        attachLanes();
        attachPlayer();
        initEffectTimer();
    }
    else if (getIntent()->getAction() == ACTION_CONTINUE_GAME) {
        loadGame();
    }
    else {
        std::cerr << "Unknown action: " << getIntent()->getAction() << std::endl;
    }
}

void GameActivity::onResume()
{
    // ...
}

void GameActivity::onPause()
{
    // ...
}

void GameActivity::onDestroy()
{
    if (!isGameOver()) {
        saveGame();
    } else {
        savePlayerScore();
    }

    MusicPlayer::getInstance().setVolume(100.f);
    MusicPlayer::getInstance().stop();
    MusicPlayer::getInstance().play(MusicID::backgroundMusic);
}

void GameActivity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.setView(target.getDefaultView());
    target.draw(*effectLayer, states);
    target.draw(*statusLayer, states);
}

void GameActivity::onEvent(const sf::Event &event)
{
    CommandQueue &commands = getCommandQueue();
    for (Player& mPlayer : mPlayers) {
        mPlayer.handleEvent(event, commands);
    }
}

void GameActivity::onEventProcessing()
{
    // mPlayer.handleRealtimeInput(getCommandQueue());
}

void GameActivity::updateCurrent(sf::Time dt)
{
    scroll(dt);
    popOutOfViewLanes();
    ensureEnoughLanes();

    while (!mCommandQueue.isEmpty()) {
        Command command = mCommandQueue.pop();
        onCommand(command, dt);
    }

    for (PlayerNode* playerNode : mPlayerNodes) {
        handleCollisions(playerNode);
    }

    updateScore();

    mEffectTimer[isEffectShown()].update(dt);
    if (mEffectTimer[isEffectShown()].isTimeout()) {
        toggleEffect();
        mEffectTimer[isEffectShown()].restart();
    }
    effectLayer->update(dt);
}

void GameActivity::drawCurrent(sf::RenderTarget &target,
                               sf::RenderStates states) const
{
    target.setView(mWorldView);
}

void GameActivity::onActivityResult(int requestCode, int resultCode,
                                    Intent::Ptr data)
{
    // ...
}

bool GameActivity::matchesCategories(ViewGroup::Pair &colliders,
                                     unsigned int type1, unsigned int type2)
{
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if ((type1 & category1) && (type2 & category2))
    {
        return true;
    }
    else if ((type1 & category2) && (type2 & category1))
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void GameActivity::handleCollisions(PlayerNode* playerNode)
{
    std::set<ViewGroup::Pair> collisionPairs;
    playerNode->checkSceneCollision(**playerNode->getCurrentLane(),
                                     collisionPairs);
    if (lanes->end() != std::next(playerNode->getCurrentLane()))
    {
        playerNode->checkSceneCollision(
            **std::next(playerNode->getCurrentLane()), collisionPairs);
    }
    playerNode->checkSceneCollision(**std::prev(playerNode->getCurrentLane()),
                                     collisionPairs);

    bool onRiver = false;
    for (ViewGroup::Pair pair : collisionPairs)
    {
        if (matchesCategories(pair, (unsigned int)(Category::Player_1) | Category::Player_2, (unsigned int)(Category::Vehicle) | Category::Animal | Category::Train))
        {
            playerNode->setDead();
        }
        else if (matchesCategories(pair, (unsigned int)(Category::Player_1) | Category::Player_2, (unsigned int)Category::Green))
        {
            playerNode->moveBack();
        }
    }

    sf::FloatRect viewBounds = getViewBounds();
    sf::FloatRect playerBounds = playerNode->getHitBox();
    if (viewBounds.top + viewBounds.height < playerBounds.top + playerBounds.height ||
        viewBounds.left + viewBounds.width < playerBounds.left ||
        viewBounds.left > playerBounds.left + playerBounds.width) {
        playerNode->setDead();
    }

    if (playerNode->isDead())
    {
        gameOver();
    }
}

void GameActivity::scroll(sf::Time dt)
{
    AppConfig &config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);

    float highestY = 0.f;
    bool flag = false;
    for (PlayerNode* playerNode : mPlayerNodes) {
        float playerY = playerNode->getWorldPosition().y;
        if (!flag || playerY < highestY) {
            highestY = playerY;
            flag = true;
        }
    }

    float different = highestY - getViewBounds().top;
    if (different < cellSize.y * 4) {
        float speed = mScrollSpeed * (1 - different / (cellSize.y * 5));
        mWorldView.move(0.f, speed * dt.asSeconds());
    }
    mWorldView.move(0.f, -50 * dt.asSeconds());
}

void GameActivity::gameOver()
{
    SoundPlayer::getInstance().play(SoundBufferID::gameOver);
    MusicPlayer::getInstance().setVolume(0.f);

    mIsGameOver = true;
    statusLayer->setIsListeningAll(false);
    createGameOverBanner();
    setUpdate(false);
    removeSavedGame();
}

bool GameActivity::isGameOver() const
{
    return mIsGameOver;
}

CommandQueue &GameActivity::getCommandQueue()
{
    return mCommandQueue;
}

void GameActivity::attachLanes()
{
    Intent *intent = getIntent();

    mMapRenderer = std::make_unique<MapRenderer>(
        mTextures, *mSceneLayers[Layer::Aboveground],
        AppConfig::getInstance().get<int>(ConfigKey::NumLaneCells),
        DEFAULT_MAP_MAX_HEIGHT, getLevel());
    lanes = &mMapRenderer->getLanes();
    unsigned int lane_index = 0;
    float const CELL_HEIGHT = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).y;
    float const TOTAL_HEIGHT = CELL_HEIGHT * lanes->size();
    for (auto it = lanes->begin(); it != lanes->end(); ++it)
    {
        Lane &lane = **it;
        lane.setPosition(0, TOTAL_HEIGHT - CELL_HEIGHT * (lane_index + 1));
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(*it));
        ++lane_index;
    }

    mWorldView.move(0.f, TOTAL_HEIGHT - CELL_HEIGHT * (DEFAULT_SPAWN_LANE_ID - 1) - mWorldView.getSize().y);
}

void GameActivity::attachPlayer()
{
    MapRenderer::LaneList::const_iterator spawnLane = std::next(lanes->begin(), DEFAULT_SPAWN_LANE_ID);

    int numPlayers = getNumPlayers();
    assert(numPlayers > 0);
    mPlayerNodes.assign(numPlayers, nullptr);
    if (numPlayers == 1) {
        mPlayers.emplace_back(Category::Player_1);
        mPlayerNodes[0] = new PlayerNode(Category::Player_1, mTextures, *lanes, spawnLane);
    } else {
        mPlayers.emplace_back(Category::Player_1);
        mPlayers.emplace_back(Category::Player_2);

        mPlayerNodes[0] = new PlayerNode(Category::Player_1, mTextures, *lanes, spawnLane);
        mPlayerNodes[1] = new PlayerNode(Category::Player_2, mTextures, *lanes, spawnLane);

        mPlayerNodes[0]->setPlayerName("P1", mFontManager.get(FontID::defaultFont));
        mPlayerNodes[1]->setPlayerName("P2", mFontManager.get(FontID::defaultFont));
    }

    for (int i = 0; i < numPlayers; ++i) {
        mPlayers[i].setActionKeys(ACTION_KEYS[i][0], ACTION_KEYS[i][1], ACTION_KEYS[i][2], ACTION_KEYS[i][3]);
    }

    for (PlayerNode* playerNode : mPlayerNodes) {
        playerNode->setOrigin(playerNode->getBoundingRect().getSize() / 2.f);
        playerNode->setTransitionLayer(mSceneLayers[Aboveground]);
        (*spawnLane)->spawnPlayer(std::unique_ptr<PlayerNode>(playerNode));
    }
}

void GameActivity::saveGameState(const std::string& gameStateFilePath, const std::string& playerStateFilePath)
{
    if (getNumPlayers() != 1) {
        std::cerr << "Cannot save game with more than 1 player" << std::endl;
        return;
    }

    std::ofstream outf(gameStateFilePath, std::ios::binary);

    float viewCenterX = mWorldView.getCenter().x;
    float viewCenterY = mWorldView.getCenter().y;

    outf.write(reinterpret_cast<const char *>(&viewCenterX), sizeof(viewCenterX));
    outf.write(reinterpret_cast<const char *>(&viewCenterY), sizeof(viewCenterY));

    bool isEffect = isEffectShown();
    outf.write(reinterpret_cast<const char *>(&isEffect), sizeof(isEffect));

    MyTimer::MyTimerData noEffectTimer = mEffectTimer[0].serialize();
    outf.write(reinterpret_cast<const char *>(&noEffectTimer), sizeof(noEffectTimer));
    MyTimer::MyTimerData effectTimer = mEffectTimer[1].serialize();
    outf.write(reinterpret_cast<const char *>(&effectTimer), sizeof(effectTimer));

    mMapRenderer->saveLanes(outf);
    outf.close();

    outf.open(playerStateFilePath, std::ios::binary);
    mPlayerNodes[0]->savePlayerData(outf); 
    outf.close();
}

void GameActivity::loadGameState(const std::string& gameStateFilePath, const std::string& playerStateFilePath)
{
    std::ifstream inf(gameStateFilePath, std::ios::binary);

    float viewCenterX;
    float viewCenterY;
    inf.read(reinterpret_cast<char *>(&viewCenterX), sizeof(viewCenterX));
    inf.read(reinterpret_cast<char *>(&viewCenterY), sizeof(viewCenterY));

    mWorldView.setCenter(viewCenterX, viewCenterY);

    bool isEffect;
    inf.read(reinterpret_cast<char *>(&isEffect), sizeof(isEffect));
    if (isEffect) {
        showEffect();
    } else {
        hideEffect();
    }

    MyTimer::MyTimerData noEffectTimer;
    inf.read(reinterpret_cast<char *>(&noEffectTimer), sizeof(noEffectTimer));
    mEffectTimer[0].deserialize(noEffectTimer);
    MyTimer::MyTimerData effectTimer;
    inf.read(reinterpret_cast<char *>(&effectTimer), sizeof(effectTimer));
    mEffectTimer[1].deserialize(effectTimer);

    mMapRenderer = std::make_unique<MapRenderer>(
        mTextures, *mSceneLayers[Layer::Aboveground],
        AppConfig::getInstance().get<int>(ConfigKey::NumLaneCells),
        DEFAULT_MAP_MAX_HEIGHT, 0, true);

    mMapRenderer->loadLanes(inf);

    inf.close();

    lanes = &mMapRenderer->getLanes();
    unsigned int lane_index = 0;
    float const CELL_HEIGHT = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize).y;
    float const TOTAL_HEIGHT = CELL_HEIGHT * lanes->size();
    for (auto it = lanes->begin(); it != lanes->end(); ++it)
    {
        Lane &lane = **it;
        lane.setPosition(0, TOTAL_HEIGHT - CELL_HEIGHT * (lane_index + 1));
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(*it));
        ++lane_index;
    }

    loadPlayer(playerStateFilePath);
}

void GameActivity::loadPlayer(const std::string& playerStateFilePath)
{
    std::ifstream inf(playerStateFilePath, std::ios::binary);

    mPlayers.emplace_back(Category::Player_1);
    mPlayers[0].setActionKeys(ACTION_KEYS[0][0], ACTION_KEYS[0][1], ACTION_KEYS[0][2], ACTION_KEYS[0][3]);

    mPlayerNodes.assign(1, nullptr);
    auto player = std::make_unique<PlayerNode>(mTextures, *lanes);
    mPlayerNodes[0] = player.get();
    mPlayerNodes[0]->setOrigin(mPlayerNodes[0]->getBoundingRect().getSize() / 2.f);
    mSceneLayers[Aboveground]->attachView(std::move(player));

    mPlayerNodes[0]->loadPlayerData(inf);
    mPlayerNodes[0]->setTransitionLayer(mSceneLayers[Aboveground]);

    MapRenderer::LaneList::const_iterator spawnLane;
    float minDistance = std::numeric_limits<float>::max();
    for (auto it = lanes->begin(); it != lanes->end(); ++it) {
        float distance = (*it)->getNearestDistance(mPlayerNodes[0]);
        if (distance < minDistance) {
            minDistance = distance;
            spawnLane = it;
        }
    }

    mPlayerNodes[0]->setCurrentLane(spawnLane);
    (*spawnLane)->receivePlayer(mPlayerNodes[0]);
}

void GameActivity::createStatusLayer() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    mScoreTexts.assign(getNumPlayers(), nullptr);
    for (int i = 0; i < (int)mScoreTexts.size(); ++i) {
        TextView::Ptr pointView = std::make_unique<TextView>(
            this,
            "0",
            mFontManager.get(FontID::defaultFont),
            sf::Vector2f(10, 10),
            48
        );
        pointView->setFillColor(sf::Color::White);
        pointView->setPosition(10, (pointView->getGlobalBounds().getSize().y + 10) * i + 10);
        mScoreTexts[i] = pointView.get();
        statusLayer->attachView(std::move(pointView));
    }

    SpriteView::Ptr menuView = std::make_unique<SpriteView>(
        this,
        mTextures.get(TextureID::mainMenuButtonTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(90, 25) * 5.f,
        sf::IntRect(99, 4, 90, 25)
    );
    sf::Vector2f menuSize = menuView->get().getGlobalBounds().getSize();
    menuView->setOrigin(menuSize / 2.f);
    menuView->setPosition(windowSize / 2.f);
    menuView->setVisibility(false);
    pauseMenu = menuView.get();

    SpriteButtonView::Ptr pauseButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::pauseButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->setUpdate(false);
            this->pauseMenu->setVisibility(true);
            this->pauseMenu->setIsListeningAll(true);
        }
    );
    pauseButton->setOrigin(pauseButton->getGlobalBounds().getSize().x, 0);
    pauseButton->setPosition(windowSize.x - 10.f, 10.f);

    SpriteButtonView::Ptr continueButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::continueButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->setUpdate(true);
            this->pauseMenu->setVisibility(false);
            this->pauseMenu->setIsListeningAll(false);
        }
    );

    SpriteButtonView::Ptr homeButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::homeButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->finish();
        }
    );
    homeButton->setOrigin(homeButton->getGlobalBounds().getSize() / 2.f);

    SpriteButtonView::Ptr settingButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::settingButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            Intent::Ptr intent = Intent::Builder()
                    .setAction(SettingsActivity::ACTION_INGAME)
                    .build();
            this->startActivity(ActivityFactory<SettingsActivity>::createInstance(), std::move(intent));
        }
    );

    float padding = 125;
    continueButton->setPosition(-padding, 0);
    settingButton->setPosition(padding, 0);
    homeButton->setPosition(menuSize / 2.f);

    homeButton->attachView(std::move(continueButton));
    homeButton->attachView(std::move(settingButton));
    menuView->attachView(std::move(homeButton));
    menuView->setIsListeningAll(false);

    statusLayer->attachView(std::move(pauseButton));
    statusLayer->attachView(std::move(menuView));
}

void GameActivity::initEffectTimer() {
    mEffectTimer[0] = MyTimer(RAIN_EFFECT_DURATION[getLevel()][0][0], RAIN_EFFECT_DURATION[getLevel()][0][1]);
    mEffectTimer[1] = MyTimer(RAIN_EFFECT_DURATION[getLevel()][1][0], RAIN_EFFECT_DURATION[getLevel()][1][1]);
    mEffectTimer[0].restart();
}

void GameActivity::createGameOverBanner() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    ButtonView::Ptr bannerView = std::make_unique<ButtonView>(
        this,
        mTextures.get(TextureID::mainMenuButtonTexture),
        mFontManager.get(FontID::defaultFont),
        "Game Over",
        64,
        sf::Vector2f(0, 0),
        sf::IntRect(99, 4, 90, 25),
        sf::Vector2f(90, 25) * 5.f
    );
    sf::Vector2f bannerSize = bannerView->getGlobalBounds().getSize();
    bannerView->setOrigin(bannerSize.x / 2.f, bannerSize.y / 2.f);
    bannerView->setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

    SpriteButtonView::Ptr replayButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::replayButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            Intent::Ptr resIntent = Intent::Builder()
                .setAction(GameActivity::ACTION_NEW_GAME)
                .putExtra(EXTRA_GAME_LEVEL, this->getLevel())
                .putExtra(EXTRA_NUM_PLAYERS, this->getNumPlayers())
                .build();
            this->setResult(RESULT_OK, std::move(resIntent));
            this->finish();
        }
    );
    replayButton->setOrigin(replayButton->getGlobalBounds().getSize().x / 2.f, 0);

    SpriteButtonView::Ptr homeButton = IconButtonFactory::create(
        this,
        mTextures.get(TextureID::homeButtonsTexture),
        mFontManager.get(FontID::defaultFont),
        sf::Vector2f(0, 0),
        [this](EventListener* listener, const sf::Event& event) {
            this->finish();
        }
    );
    homeButton->setOrigin(homeButton->getGlobalBounds().getSize().x / 2.f, 0);

    float paddingX = 100;
    float paddingY = 10;
    replayButton->setPosition(bannerSize.x / 2.f - paddingX, bannerSize.y + paddingY);
    homeButton->setPosition(bannerSize.x / 2.f + paddingX, bannerSize.y + paddingY);

    bannerView->attachView(std::move(replayButton));
    bannerView->attachView(std::move(homeButton));
    statusLayer->attachView(std::move(bannerView));
}

void GameActivity::createEffectLayer() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);
    LayerView::Ptr rainLayer = std::make_unique<RainLayer>(windowSize);
    effectLayer->attachView(std::move(rainLayer));
    effectLayer->setVisibility(false);
}

void GameActivity::showEffect() {
    effectLayer->setVisibility(true);
    for (PlayerNode* playerNode : mPlayerNodes) {
        playerNode->slowDown();
    }
}

void GameActivity::hideEffect() {
    effectLayer->setVisibility(false);
    for (PlayerNode* playerNode : mPlayerNodes) {
        playerNode->speedUp();
    }
}

void GameActivity::toggleEffect() {
    if (isEffectShown()) {
        hideEffect();
    } else {
        showEffect();
    }

}

bool GameActivity::isEffectShown() const {
    return effectLayer->isVisible();
}

void GameActivity::updateScore() {
    if (getNumPlayers() == 1) {
        mScoreTexts[0]->setText(std::to_string(mPlayerNodes[0]->getScore()));
    } else if (getNumPlayers() == 2) {
        mScoreTexts[0]->setText("P1: " + std::to_string(mPlayerNodes[0]->getScore()));
        mScoreTexts[1]->setText("P2: " + std::to_string(mPlayerNodes[1]->getScore()));
    }
}

void GameActivity::ensureEnoughLanes() {
    // generate new lanes when there are few lanes left
    if (lanes->size() < DEFAULT_MAP_MAX_HEIGHT)
    {
        
        Lane* newLane = mMapRenderer->createNewLane();
        mSceneLayers[Background]->attachView(std::unique_ptr<ViewGroup>(newLane));
        mWorldView.move(0.f, newLane->getSize().y);
        for (PlayerNode* playerNode : mPlayerNodes) {
            if (playerNode->isMoving()) {
                playerNode->move(0.f, newLane->getSize().y);
            }
        }
    }
}

void GameActivity::popOutOfViewLanes() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f cellSize = config.get<sf::Vector2f>(ConfigKey::CellSize);
    float threshold = cellSize.y * 5;

    sf::FloatRect worldBounds = getViewBounds();
    while (!lanes->empty() && lanes->front()->getPosition().y > worldBounds.top + worldBounds.height + threshold) {
        mMapRenderer->popLane();
    }
}

sf::FloatRect GameActivity::getViewBounds() const {
    sf::FloatRect rt;
    rt.left = mWorldView.getCenter().x - mWorldView.getSize().x/2.f;
    rt.top  = mWorldView.getCenter().y - mWorldView.getSize().y/2.f;
    rt.width  = mWorldView.getSize().x;
    rt.height = mWorldView.getSize().y;
    return rt;
}

void GameActivity::saveGame() {
    if (getNumPlayers() != 1) {
        std::cerr << "Only support single player game.\n";
        return;
    }

    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = userSession.getCurrentUser().getUsername();
    std::string dirPath = dataPath + username;

    UtilitySave::DeleteDirContent(dirPath);
    std::error_code err;
    if (!UtilitySave::CreateDirectoryRecursive(dirPath, err)) {
        std::cerr << "SAVE FAILURE, ERR: " << err << std::endl;
    }

    std::string gameStateFilePath = dirPath + "/" + GAME_STATE_FILENAME;
    std::string playerStateFilePath = dirPath + "/" + PLAYER_STATE_FILENAME;
    saveGameState(gameStateFilePath, playerStateFilePath);
}

void GameActivity::loadGame() {
    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = userSession.getCurrentUser().getUsername();
    std::string gameStateFilePath = dataPath + username + "/" + GAME_STATE_FILENAME;
    std::string playerStateFilePath = dataPath + username + "/" + PLAYER_STATE_FILENAME;
    loadGameState(gameStateFilePath, playerStateFilePath);
}

void GameActivity::removeSavedGame() {
    if (getNumPlayers() != 1) {
        std::cerr << "Only support single player game.\n";
        return;
    }

    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = userSession.getCurrentUser().getUsername();
    std::string dirPath = dataPath + username;

    UtilitySave::DeleteDirContent(dirPath);
}

void GameActivity::savePlayerScore() {
    if (getNumPlayers() != 1) {
        std::cerr << "Only support single player game.\n";
        return;
    }

    UserSession& userSession = UserSession::getInstance();
    if (!userSession.isLoggedin()) {
        std::cerr << "User not logged in.\n";
        return;
    }
    UserData& user = userSession.getCurrentUser();
    GameLevel level = (GameLevel)mMapRenderer->getLevel();
    UserData::GameMode mode;

    switch(level) {
        case GameLevel::Easy:
            mode = UserData::GameMode::easy;
        break;
        case GameLevel::Medium:
            mode = UserData::GameMode::medium;
        break;
        case GameLevel::Hard:
            mode = UserData::GameMode::hard;
        break;
        case GameLevel::Insane:
            mode = UserData::GameMode::insane;
        break;
        case GameLevel::RainDay:
            mode = UserData::GameMode::rainday;
        break;
        case GameLevel::Endless:
            mode = UserData::GameMode::endless;
        break;
        default:
            assert(false);
    }

    user.updateHighscore(mPlayerNodes[0]->getScore(), mode);

    UserRepo& userRepo = UserRepo::getInstance();
    userRepo.updateUser(user);
}

int GameActivity::getLevel() const {
    if (mMapRenderer == nullptr) {
        return getIntent()->getExtra<int>(EXTRA_GAME_LEVEL);
    }
    return mMapRenderer->getLevel();
}

int GameActivity::getNumPlayers() const {
    return getIntent()->getExtra<int>(EXTRA_NUM_PLAYERS);
}