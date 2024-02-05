#include <MainMenuActivity.hpp>

#include <AppConfig.hpp>

#include <ButtonView.hpp>
#include <SpriteButtonView.hpp>
#include <TextView.hpp>
#include <SpriteView.hpp>
#include <SpriteSheetView.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <MenuButtonFactory.hpp>

#include <ActivityFactory.hpp>
#include <LevelsActivity.hpp>

#include <RankingActivity.hpp>
#include <SettingsActivity.hpp>
#include <ProfileActivity.hpp>
#include <HelpActivity.hpp>

#include <MusicPlayer.hpp>

#include <GameSetting.hpp>

void MainMenuActivity::onLoadResources() {
    mFontHolder.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureHolder.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");
    mTextureHolder.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureHolder.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureHolder.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureHolder.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureHolder.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void MainMenuActivity::onCreate() {
    GameSetting::getInstance().loadSettingState();
    createBackground();
    createTitle();
    createPlayButtons();
}

void MainMenuActivity::onAttach() {
    MusicPlayer::getInstance().play(MusicID::backgroundMusic);
}

void MainMenuActivity::onResume() {
    // ...
}

void MainMenuActivity::onPause() {
    // ...
}

void MainMenuActivity::onDestroy() {
    MusicPlayer::getInstance().stop();
}

void MainMenuActivity::onEvent(const sf::Event& event) {
    // ...
}

void MainMenuActivity::updateCurrent(sf::Time dt) {
    // ...
}

void MainMenuActivity::onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data) {
    if (requestCode == (int)Request::REQUEST_CODE_GAME_LEVEL || 
        requestCode == (int)Request::REQUEST_CODE_CONTINUE_GAME || 
        requestCode == (int)Request::REQUEST_CODE_NEW_GAME) {
        if (resultCode == ResultCode::RESULT_OK) {
            if (data->getAction() == (int)GameActivity::Action::ACTION_NEW_GAME) {
                data->setRequestCode((int)Request::REQUEST_CODE_NEW_GAME);
                startActivity(ActivityFactory<GameActivity>::createInstance(), std::move(data));
            }
        }
    } else if (requestCode == (int)Request::REQUEST_TITLEBAR_BUTTONS) {
        if (resultCode == ResultCode::RESULT_OK) {
            int titleType = data->getExtra<int>("titleType", -1);
            if (titleType == -1) {
                return;
            }
            Intent::Ptr intent = Intent::Builder()
                .setRequestCode((int)Request::REQUEST_TITLEBAR_BUTTONS)
                .build();
            if (titleType == (int)TitlebarFactory::TitlebarType::SETTINGS) {
                startActivity(ActivityFactory<SettingsActivity>::createInstance(), std::move(intent));
            } else if (titleType == (int)TitlebarFactory::TitlebarType::HELP) {
                startActivity(ActivityFactory<HelpActivity>::createInstance(), std::move(intent));
            } else if (titleType == (int)TitlebarFactory::TitlebarType::PROFILE) {
                startActivity(ActivityFactory<ProfileActivity>::createInstance(), std::move(intent));
            }
        }
    }
}

void MainMenuActivity::createBackground() {
    attachView(BackgroundFactory::create(
        this,
        mTextureHolder.get(TextureID::mainMenuBackgroundTexture)
    ));
} 

void MainMenuActivity::createTitle() {
    attachView(TitlebarFactory::create(
        this,
        mTextureHolder,
        mFontHolder.get(FontID::defaultFont),
        "Main Menu",
        TitlebarFactory::TitlebarType::NONE,
        (int)Request::REQUEST_TITLEBAR_BUTTONS
    ));
}

void MainMenuActivity::createPlayButtons() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 320;
    float height = 128;
    sf::Vector2f position((windowSize.x-width)/2, 300);
    sf::Vector2f spacing(0, height + 2);

    sf::Texture& buttonTexture = mTextureHolder.get(TextureID::mainMenuButtonTexture);

    SpriteButtonView::Ptr playButton = MenuButtonFactory::create(this, buttonTexture, mFontHolder.get(FontID::defaultFont), "New game", position, [this](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode((int)Request::REQUEST_CODE_GAME_LEVEL)
            .build();
        this->startActivity(ActivityFactory<LevelsActivity>::createInstance(), std::move(intent));
    });

    SpriteButtonView::Ptr continueButton = MenuButtonFactory::create(this, buttonTexture, mFontHolder.get(FontID::defaultFont), "Continue", spacing, [this](EventListener* listener, const sf::Event& event) {
        if (!this->savedGameExists()) {
            return;
        }
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode((int)Request::REQUEST_CODE_CONTINUE_GAME)
            .setAction((int)GameActivity::Action::ACTION_CONTINUE_GAME)
            .putExtra(GameActivity::EXTRA_NUM_PLAYERS, 1)
            .build();
        this->startActivity(ActivityFactory<GameActivity>::createInstance(), std::move(intent));
    });

    SpriteButtonView::Ptr rankingsButton = MenuButtonFactory::create(this, buttonTexture, mFontHolder.get(FontID::defaultFont), "Rankings", spacing, [this](EventListener* listener, const sf::Event& event) {
        this->startActivity(ActivityFactory<RankingActivity>::createInstance());
    });

    SpriteButtonView::Ptr exitButton = MenuButtonFactory::create(this, buttonTexture, mFontHolder.get(FontID::defaultFont), "Exit", spacing, [&](EventListener* listener, const sf::Event& event) {
        std::cerr << " >> Exit" << std::endl;
        this->finish();
    });

    rankingsButton->attachView(std::move(exitButton));
    continueButton->attachView(std::move(rankingsButton));
    playButton->attachView(std::move(continueButton));
    attachView(std::move(playButton));
}

bool MainMenuActivity::savedGameExists() {
    UserSession& session = UserSession::getInstance();
    if (!session.isLoggedin()) {
        return false;
    }
    AppConfig& config = AppConfig::getInstance();
    std::string dataPath = config.get<std::string>(ConfigKey::DATA_PATH);
    std::string username = session.getCurrentUser().getUsername();
    std::string dirPath = dataPath + username;
    return std::filesystem::exists(dirPath);
}