#include <HelpActivity.hpp>
#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>

void HelpActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void HelpActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
}

void HelpActivity::onAttach() {
    // ...
}

void HelpActivity::onResume() {
    // ...
}

void HelpActivity::onPause() {
    // ...
}

void HelpActivity::onDestroy() {
    // ...
}

void HelpActivity::onEvent(const sf::Event& event) {
    // ...
}

void HelpActivity::updateCurrent(sf::Time dt) {
    // ...
}

void HelpActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureManager.get(TextureID::squareButtonsTexture),
            mFontManager.get(FontID::defaultFont)
        )
    );
}

void HelpActivity::createBackground() {
    attachView(
        BackgroundFactory::create(mTextureManager.get(TextureID::mainMenuBackgroundTexture))
    );
}

void HelpActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureManager,
            mFontManager.get(FontID::defaultFont),
            "Help",
            TitlebarFactory::TitlebarType::HELP,
            REQUEST_TITLEBAR_BUTTONS
        )
    );
}