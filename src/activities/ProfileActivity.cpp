#include <ProfileActivity.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>
#include <MenuButtonFactory.hpp>

#include <ActivityProfile.hpp>

#include <RectangleView.hpp>
#include <TextView.hpp>

#include <UserSession.hpp>
#include <AppConfig.hpp>
#include <LoginActivity.hpp>

void ProfileActivity::onLoadResources()
{
    mFontHolder.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureHolder.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");
    mTextureHolder.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
    mTextureHolder.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureHolder.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureHolder.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureHolder.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureHolder.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void ProfileActivity::onCreate()
{
    createBackground();
    createTitle();
    createBackButton();
    createProfile();
}

void ProfileActivity::onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_LOG_IN) {
        if (resultCode == Activity::ResultCode::RESULT_OK) {
            std::string username = data->getExtra<std::string>("username");
            std::string password = data->getExtra<std::string>("password");
            UserSession &userSession = UserSession::getInstance();
            userSession.loginUser(username, password);
            Intent::Ptr intent = Intent::Builder()
                                     .putExtra("titleType", TitlebarFactory::TitlebarType::PROFILE)
                                     .build();
            setResult(Activity::ResultCode::RESULT_OK, std::move(intent));
            finish();
        }
        else if (resultCode == Activity::ResultCode::RESULT_CANCELED) {
            // ...
        }
    }
}

void ProfileActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureHolder.get(TextureID::squareButtonsTexture),
            mFontHolder.get(FontID::defaultFont)));
}

void ProfileActivity::createBackground() {
    attachView(
        BackgroundFactory::create(
            this,
            mTextureHolder.get(TextureID::mainMenuBackgroundTexture)));
}

void ProfileActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureHolder,
            mFontHolder.get(FontID::defaultFont),
            "Profile",
            TitlebarFactory::TitlebarType::PROFILE,
            REQUEST_TITLEBAR_BUTTONS));
}

void ProfileActivity::createProfile() {
    AppConfig &config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    SpriteView::Ptr menu = std::make_unique<SpriteView>(
        this,
        mTextureHolder.get(TextureID::settingMenuTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(106, 122) * 5.f,
        sf::IntRect(139, 12, 106, 122));
    menu->setPosition((windowSize - menu->get().getGlobalBounds().getSize()) / 2.f + sf::Vector2f(0, 100));

    UserSession &userSession = UserSession::getInstance();

    if (userSession.isLoggedin())
    {
        createUserProfile(menu.get());
    }
    else
    {
        createGuessProfile(menu.get());
    }

    attachView(std::move(menu));
}

void ProfileActivity::createGuessProfile(SpriteView *dialog) {
    SpriteButtonView::Ptr loginButton = MenuButtonFactory::create(
        this,
        mTextureHolder.get(TextureID::mainMenuButtonTexture),
        mFontHolder.get(FontID::defaultFont),
        "Sign in",
        sf::Vector2f(),
        [&](EventListener *listener, const sf::Event &event)
        {
            Intent::Ptr intent = Intent::Builder()
                                     .setRequestCode(REQUEST_LOG_IN)
                                     .build();
            this->startActivity(ActivityID::Login, std::move(intent));
        });
    loginButton->setPosition((dialog->get().getGlobalBounds().getSize() - loginButton->getGlobalBounds().getSize()) / 2.f);

    dialog->attachView(std::move(loginButton));
}

void ProfileActivity::createUserProfile(SpriteView *dialog) {
    UserRepo &userRepo = UserRepo::getInstance();
    UserSession &userSession = UserSession::getInstance();
    UserData &userData = userSession.getCurrentUser();

    TextView::Ptr usernameView = std::make_unique<TextView>(
        this,
        userData.getUsername(),
        mFontHolder.get(FontID::defaultFont),
        sf::Vector2f(50, 50),
        64,
        sf::Color::White);

    RectangleView::Ptr underlineView = std::make_unique<RectangleView>(
        this,
        sf::Vector2f(usernameView->getGlobalBounds().getSize().x + 20, 4),
        sf::Vector2f(0, usernameView->getGlobalBounds().getSize().y + 10),
        sf::Color::White);

    usernameView->attachView(std::move(underlineView));

    SpriteButtonView::Ptr logoutButton = MenuButtonFactory::create(
        this,
        mTextureHolder.get(TextureID::mainMenuButtonTexture),
        mFontHolder.get(FontID::defaultFont),
        "Sign out",
        sf::Vector2f(),
        [this](EventListener *listener, const sf::Event &event)
        {
            UserSession &userSession = UserSession::getInstance();
            userSession.logoutUser();
            this->finish();
        });
    logoutButton->setPosition((dialog->get().getGlobalBounds().getSize() - logoutButton->getGlobalBounds().getSize()) / 2.f);
    logoutButton->move(0, 150);

    dialog->attachView(std::move(usernameView));
    dialog->attachView(std::move(logoutButton));
}