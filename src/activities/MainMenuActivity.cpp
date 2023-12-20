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
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
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
    static float ratio = 1;
    static float delta = 0.01;
    static float angle = 0;
    static sf::View view = getActivityManager()->getWindow().getView();
    view.rotate(angle);
    view.zoom(ratio);
    getActivityManager()->getWindow().setView(view);
    view.zoom(1/ratio);
    angle += 0.001;
    if (angle >= 360) {
        angle = 0;
    }
    ratio += delta;
    if (ratio >= 2) delta = -0.01;
    if (ratio <= 0.5) delta = 0.01;
    // std::cerr << ratio << ' ' << delta << '\n';
}

void MainMenuActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_CODE_GAME_LEVEL) {
        if (resultCode == (int)ResultCode::RESULT_OK) {
            startActivity(ActivityFactory<GameActivity>::createInstance(), std::move(data));
        }
    } else if (requestCode == REQUEST_TITLEBAR_BUTTONS) {
        if (resultCode == (int)ResultCode::RESULT_OK) {
            int titleType = data->getExtra<int>("titleType", -1);
            if (titleType == -1) {
                std::cerr << " >> MainMenuActivity::onActivityResult: titleType is not set" << std::endl;
                return;
            }
            Intent::Ptr intent = Intent::Builder()
                .setRequestCode(REQUEST_TITLEBAR_BUTTONS)
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
        mTextureManager.get(TextureID::mainMenuBackgroundTexture)
    ));
} 

void MainMenuActivity::createTitle() {
    attachView(TitlebarFactory::create(
        this,
        mTextureManager,
        mFontManager.get(FontID::defaultFont),
        "Main Menu",
        TitlebarFactory::TitlebarType::NONE,
        REQUEST_TITLEBAR_BUTTONS
    ));
}

void MainMenuActivity::createPlayButtons() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 320;
    float height = 128;
    sf::Vector2f position((windowSize.x-width)/2, 300);
    sf::Vector2f spacing(0, height + 2);

    sf::Texture& buttonTexture = mTextureManager.get(TextureID::mainMenuButtonTexture);

    SpriteButtonView::Ptr playButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "New game", position, [this](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode(REQUEST_CODE_GAME_LEVEL)
            .build();
        this->startActivity(ActivityFactory<LevelsActivity>::createInstance(), std::move(intent));
    });

    SpriteButtonView::Ptr continueButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Continue", spacing, [this](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode(REQUEST_CODE_CONTINUE_GAME)
            .setAction(GameActivity::ACTION_CONTINUE_GAME)
            .build();
        this->startActivity(ActivityFactory<GameActivity>::createInstance(), std::move(intent));
    });

    SpriteButtonView::Ptr rankingsButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Rankings", spacing, [this](EventListener* listener, const sf::Event& event) {
        this->startActivity(ActivityFactory<RankingActivity>::createInstance());
    });

    SpriteButtonView::Ptr exitButton = MenuButtonFactory::create(this, buttonTexture, mFontManager.get(FontID::defaultFont), "Exit", spacing, [&](EventListener* listener, const sf::Event& event) {
        std::cerr << " >> Exit" << std::endl;
        this->finish();
    });

    rankingsButton->attachView(std::move(exitButton));
    continueButton->attachView(std::move(rankingsButton));
    playButton->attachView(std::move(continueButton));
    attachView(std::move(playButton));
}