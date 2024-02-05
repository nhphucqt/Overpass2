#include <SettingsActivity.hpp>
#include <AppConfig.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>
#include <ToggleButtonView.hpp>
#include <SpriteView.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>
#include <SettingToggleFactory.hpp>

#include <GameSetting.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>

void SettingsActivity::onLoadResources() {
    mFontHolder.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureHolder.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureHolder.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureHolder.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureHolder.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureHolder.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
    mTextureHolder.load(TextureID::toggleButtonsTexture, "res/textures/ui/UI_Settings_Buttons.png");
    mTextureHolder.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
}

void SettingsActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createMenu();
}

void SettingsActivity::createBackground() {
    attachView(
        BackgroundFactory::create(this, mTextureHolder.get(TextureID::mainMenuBackgroundTexture))
    );
}

void SettingsActivity::createTitle() {
    int requestCode = getIntent()->getAction() == ACTION_INGAME ? -1 : REQUEST_TITLEBAR_BUTTONS;
    attachView(
        TitlebarFactory::create(
            this,
            mTextureHolder,
            mFontHolder.get(FontID::defaultFont),
            "Settings",
            TitlebarFactory::TitlebarType::SETTINGS,
            requestCode
        )
    );
}

void SettingsActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureHolder.get(TextureID::squareButtonsTexture),
            mFontHolder.get(FontID::defaultFont)
        )
    );
}

void SettingsActivity::createMenu() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    SpriteView::Ptr menu = std::make_unique<SpriteView>(
        this,
        mTextureHolder.get(TextureID::settingMenuTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(106, 122) * 4.f,
        sf::IntRect(139, 12, 106, 122)
    );
    menu->setPosition((windowSize - menu->get().getGlobalBounds().getSize()) / 2.f + sf::Vector2f(0, 100));

    ToggleButtonView::Ptr musicToggle = SettingToggleFactory::create(
        this,
        mTextureHolder.get(TextureID::toggleButtonsTexture),
        mFontHolder.get(FontID::defaultFont),
        "Music",
        false
    );
    musicToggle->setPosition((menu->get().getGlobalBounds().getSize() - musicToggle->getGlobalBounds().getSize() - sf::Vector2f(0, musicToggle->getGlobalBounds().getSize().y + 20)) / 2.f);
    musicToggle->move(30, 0);

    ToggleButtonView::Ptr soundToggle = SettingToggleFactory::create(
        this,
        mTextureHolder.get(TextureID::toggleButtonsTexture),
        mFontHolder.get(FontID::defaultFont),
        "Sound",
        false
    );
    soundToggle->move(0, musicToggle->getGlobalBounds().getSize().y + 20);

    MusicPlayer& musicPlayer = MusicPlayer::getInstance();
    SoundPlayer& soundPlayer = SoundPlayer::getInstance();

    musicToggle->setState(!musicPlayer.isMuted());
    soundToggle->setState(!soundPlayer.isMuted());

    musicToggle->setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {
        ToggleButtonView* button = dynamic_cast<ToggleButtonView*>(listener);
        if (button->getState()) {
            musicPlayer.setMute(false);
        } else {
            musicPlayer.setMute(true);
        }
        GameSetting::getInstance().saveSettingState();
    });

    soundToggle->setOnMouseButtonReleased([&](EventListener* listener, const sf::Event& event) {
        ToggleButtonView* button = dynamic_cast<ToggleButtonView*>(listener);
        if (button->getState()) {
            soundPlayer.setMute(false);
        } else {
            soundPlayer.setMute(true);
        }
        GameSetting::getInstance().saveSettingState();
    });
    
    musicToggle->attachView(std::move(soundToggle));
    menu->attachView(std::move(musicToggle));
    attachView(std::move(menu));
}