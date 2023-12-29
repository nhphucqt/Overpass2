#include <SignupActivity.hpp>
#include <ResourceID.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>
#include <EditTextView.hpp>
#include <AppConfig.hpp>
#include <UserRepo.hpp>

#include <BackgroundFactory.hpp>
#include <TitlebarFactory.hpp>
#include <BackButtonFactory.hpp>
#include <InputFieldFactory.hpp>
#include <MenuButtonFactory.hpp>

void SignupActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuButtonTexture, "res/textures/ui/UI_Big_Play_Button.png");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
}

void SignupActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createDialog();
}

void SignupActivity::onAttach() {
    // ...
}

void SignupActivity::onResume() {
    // ...
}

void SignupActivity::onPause() {
    // ...
}

void SignupActivity::onDestroy() {
    // ...
}

void SignupActivity::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Tab) {
            if (mUsername->isFocused()) {
                mUsername->setFocused(false);
                mPassword->setFocused(true);
                mConfirmPassword->setFocused(false);
            } else if (mPassword->isFocused()) {
                mUsername->setFocused(false);
                mPassword->setFocused(false);
                mConfirmPassword->setFocused(true);
            } else if (mConfirmPassword->isFocused()) {
                mUsername->setFocused(true);
                mPassword->setFocused(false);
                mConfirmPassword->setFocused(false);
            } else {
                mUsername->setFocused(true);
            }
        } else if (event.key.code == sf::Keyboard::Return) {
            checkSignup(mUsername->getText(), mPassword->getText(), mConfirmPassword->getText());
        }
    }
}

void SignupActivity::updateCurrent(sf::Time dt) {
    // ...
}

void SignupActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    // ...
}

void SignupActivity::createBackground() {
    attachView(BackgroundFactory::create(
        mTextureManager.get(TextureID::mainMenuBackgroundTexture)
    ));
}

void SignupActivity::createTitle() {
    attachView(TitlebarFactory::create(
        this,
        mTextureManager,
        mFontManager.get(FontID::defaultFont),
        "Sign up",
        TitlebarFactory::TitlebarType::NONE,
        REQUEST_TITLEBAR_BUTTONS
    ));
}

void SignupActivity::createBackButton() {
    attachView(BackButtonFactory::create(
        this,
        mTextureManager.get(TextureID::squareButtonsTexture),
        mFontManager.get(FontID::defaultFont)
    ));
}

void SignupActivity::createDialog() {
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
    EditTextView::Ptr confirmPwdField = InputFieldFactory::create(this, mFontManager.get(FontID::defaultFont), "ReEnter", EditTextView::InputType::PASSWORD);
    mConfirmPassword = confirmPwdField.get();

    usrField->setPosition((menu->get().getGlobalBounds().getSize() - usrField->getGlobalBounds().getSize() - sf::Vector2f(0, usrField->getGlobalBounds().getSize().y + 20)) / 2.f);
    usrField->move(92, -156);
    pwdField->move(0, usrField->getGlobalBounds().getSize().y + 20);
    confirmPwdField->move(0, pwdField->getGlobalBounds().getSize().y + 20);

    TextView::Ptr errorView = std::make_unique<TextView>("", mFontManager.get(FontID::defaultFont), sf::Vector2f(0, pwdField->getGlobalBounds().getSize().y + 20), 36, sf::Color::Red);
    mError = errorView.get();
    errorView->move(-180, 0);

    SpriteButtonView::Ptr submitButton = MenuButtonFactory::create(this, mTextureManager.get(TextureID::mainMenuButtonTexture), mFontManager.get(FontID::defaultFont), "Sign up", sf::Vector2f(), [&](EventListener* listener, const sf::Event& event) {
        checkSignup(mUsername->getText(), mPassword->getText(), mConfirmPassword->getText());
    });
    submitButton->setPosition((menu->get().getGlobalBounds().getSize() - submitButton->getGlobalBounds().getSize()) / 2.f);
    submitButton->move(0, 180);

    confirmPwdField->attachView(std::move(errorView));
    pwdField->attachView(std::move(confirmPwdField));
    usrField->attachView(std::move(pwdField));
    menu->attachView(std::move(usrField));
    menu->attachView(std::move(submitButton));
    attachView(std::move(menu));
}

void SignupActivity::checkSignup(const std::string& username, const std::string& password, const std::string& confirmPassword) {
    if (username.empty() || password.empty() || confirmPassword.empty()) {
        std::cout << " >> Please fill all fields" << std::endl;
        mError->setText("Please fill all fields");
        return;
    }

    UserRepo& userRepo = UserRepo::getInstance();
    if (userRepo.userExist(username)) {
        std::cout << " >> Username already exists" << std::endl;
        mError->setText("Username already exists");
        return;
    }

    if (password != confirmPassword) {
        std::cout << " >> Passwords do not match" << std::endl;
        mError->setText("Passwords do not match");
        return;
    }

    UserData newUser(username, password);
    userRepo.addUser(newUser);
    std::cout << " >> Signup success: " << username << std::endl;
    Intent::Ptr resIntent = Intent::Builder()
        .putExtra("username", username)
        .putExtra("password", password)
        .build();
    setResult((int)ResultCode::RESULT_OK, std::move(resIntent));
    finish();
}