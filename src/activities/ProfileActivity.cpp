#include <ProfileActivity.hpp>
#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>

void ProfileActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void ProfileActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createProfile();
}

void ProfileActivity::onAttach() {
    // ...
}

void ProfileActivity::onResume() {
    // ...
}

void ProfileActivity::onPause() {
    // ...
}

void ProfileActivity::onDestroy() {
    // ...
}

void ProfileActivity::onEvent(const sf::Event& event) {
    // ...
}

void ProfileActivity::updateCurrent(sf::Time dt) {
    // ...
}

void ProfileActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureManager.get(TextureID::squareButtonsTexture),
            mFontManager.get(FontID::defaultFont)
        )
    );
}

void ProfileActivity::createBackground() {
    attachView(
        BackgroundFactory::create(mTextureManager.get(TextureID::mainMenuBackgroundTexture))
    );
}

void ProfileActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureManager,
            mFontManager.get(FontID::defaultFont),
            "Profile",
            TitlebarFactory::TitlebarType::PROFILE,
            REQUEST_TITLEBAR_BUTTONS
        )
    );
}

void ProfileActivity::createProfile() {
    // ...
}