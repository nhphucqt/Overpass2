#include <LoginActivity.hpp>
#include <ActivityFactory.hpp>
#include <AppConfig.hpp>
#include <ResourceID.hpp>
#include <TextView.hpp>
#include <EditTextView.hpp>
#include <ButtonView.hpp>
#include <UserRepo.hpp>
#include <SignupActivity.hpp>

#include <BackgroundFactory.hpp>
#include <TitlebarFactory.hpp>
#include <BackButtonFactory.hpp>
#include <InputFieldFactory.hpp>
#include <MenuButtonFactory.hpp>

void LoginActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void LoginActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createDialog();
}

void LoginActivity::onAttach() {
    // ...
}

void LoginActivity::onResume() {
    // ...
}

void LoginActivity::onPause() {
    // ...
}

void LoginActivity::onDestroy() {
    // ...
}

void LoginActivity::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Tab) {
            if (mUsername->isFocused()) {
                mUsername->setFocused(false);
                mPassword->setFocused(true);
            } else if (mPassword->isFocused()) {
                mPassword->setFocused(false);
                mUsername->setFocused(true);
            } else {
                mUsername->setFocused(true);
            }
        } else if (event.key.code == sf::Keyboard::Return) {
            checkLogin(mUsername->getText(), mPassword->getText());
        }
    }
}

void LoginActivity::updateCurrent(sf::Time dt) {
    // ...
}

void LoginActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_SIGN_UP) {
        if (resultCode == (int)ResultCode::RESULT_OK) { 
            setResult((int)ResultCode::RESULT_OK, std::move(data));
            finish();
        } else if (resultCode == (int)ResultCode::RESULT_CANCELED) {
            mError->setText("Sign up failed");
        }
    }
}

void LoginActivity::createBackground() {
    attachView(BackgroundFactory::create(
        mTextureManager.get(TextureID::mainMenuBackgroundTexture)
    ));
}

void LoginActivity::createTitle() {
    attachView(TitlebarFactory::create(
        this,
        mTextureManager,
        mFontManager.get(FontID::defaultFont),
        "Sign in",
        TitlebarFactory::TitlebarType::NONE,
        REQUEST_TITLEBAR_BUTTONS
    ));
}

void LoginActivity::createBackButton() {
    attachView(BackButtonFactory::create(
        this,
        mTextureManager.get(TextureID::squareButtonsTexture),
        mFontManager.get(FontID::defaultFont)
    ));
}

void LoginActivity::createDialog() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    SpriteView::Ptr menu = std::make_unique<SpriteView>(
        mTextureManager.get(TextureID::settingMenuTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(106, 122) * 5.f,
        sf::IntRect(139, 12, 106, 122)
    );
    menu->setPosition((windowSize - menu->get().getGlobalBounds().getSize()) / 2.f + sf::Vector2f(0, 100));

    EditTextView::Ptr usrField = InputFieldFactory::create(this, mFontManager.get(FontID::defaultFont), "Username", EditTextView::InputType::TEXT);
    mUsername = usrField.get();
    EditTextView::Ptr pwdField = InputFieldFactory::create(this, mFontManager.get(FontID::defaultFont), "Password", EditTextView::InputType::PASSWORD);
    mPassword = pwdField.get();

    usrField->setPosition((menu->get().getGlobalBounds().getSize() - usrField->getGlobalBounds().getSize() - sf::Vector2f(0, usrField->getGlobalBounds().getSize().y + 20)) / 2.f);
    usrField->move(92, -100);
    pwdField->move(0, usrField->getGlobalBounds().getSize().y + 20);

    TextView::Ptr errorView = std::make_unique<TextView>("", mFontManager.get(FontID::defaultFont), sf::Vector2f(0, pwdField->getGlobalBounds().getSize().y + 20), 36, sf::Color::Red);
    mError = errorView.get();
    errorView->move(-180, 0);

    SpriteButtonView::Ptr submitButton = MenuButtonFactory::create(this, mTextureManager.get(TextureID::mainMenuButtonTexture), mFontManager.get(FontID::defaultFont), "Sign in", sf::Vector2f(), [&](EventListener* listener, const sf::Event& event) {
        checkLogin(mUsername->getText(), mPassword->getText());
    });
    submitButton->setPosition((menu->get().getGlobalBounds().getSize() - submitButton->getGlobalBounds().getSize()) / 2.f);
    submitButton->move(0, 180);

    TextView::Ptr registerView = std::make_unique<TextView>("Create new account", mFontManager.get(FontID::defaultFont), sf::Vector2f(), 24, sf::Color::White);
    registerView->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        Intent::Ptr intent = Intent::Builder()
            .setRequestCode(REQUEST_SIGN_UP)
            .build();
        startActivity(ActivityFactory<SignupActivity>::createInstance(), std::move(intent));
    });
    registerView->setPosition((submitButton->getGlobalBounds().getSize() - registerView->getGlobalBounds().getSize()) / 2.f);
    registerView->move(0, 80);

    pwdField->attachView(std::move(errorView));
    usrField->attachView(std::move(pwdField));
    menu->attachView(std::move(usrField));
    submitButton->attachView(std::move(registerView));
    menu->attachView(std::move(submitButton));
    attachView(std::move(menu));
}

void LoginActivity::checkLogin(const std::string& username, const std::string& password) {
    if (!username.empty() && !password.empty() && UserRepo::getInstance().checkUser(username, password)) {
        Intent::Ptr data = std::make_unique<Intent>();
        data->putExtra("username", username);
        data->putExtra("password", password);
        setResult((int)ResultCode::RESULT_OK, std::move(data));
        finish();
    } else {
        mError->setText("Invalid username or password");
    }
}