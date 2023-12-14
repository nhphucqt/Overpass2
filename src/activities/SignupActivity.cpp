#include <SignupActivity.hpp>
#include <ResourceID.hpp>
#include <TextView.hpp>
#include <ButtonView.hpp>
#include <EditTextView.hpp>
#include <AppConfig.hpp>
#include <UserRepo.hpp>

void SignupActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/Consolas-Bold.ttf");
}

void SignupActivity::onCreate() {
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
    // ...
}

void SignupActivity::updateCurrent(sf::Time dt) {
    // ...
}

void SignupActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    // ...
}

void SignupActivity::createTitle() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    sf::Color color = sf::Color::Black;
    int fontSize = 50;

    TextView::Ptr title = std::make_unique<TextView>("Sign up", mFontManager.get(FontID::defaultFont), sf::Vector2f(), fontSize, color);
    sf::Vector2f position((windowSize.x-title->getGlobalBounds().getSize().x)/2, 50);
    title->setPosition(position);

    attachView(std::move(title));
}

void SignupActivity::createBackButton() {
    float width = 50;
    float height = 50;
    sf::Vector2f size(width, height);
    sf::Vector2f position(20, 20);
    sf::Color color = sf::Color(150, 150, 150, 255);
    int fontSize = 50;

    ButtonView::Ptr backButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "<", fontSize, position, size, color);
    backButton->setTextColor(sf::Color::Black);
    backButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        setResult((int)ResultCode::RESULT_CANCELED, nullptr);
        finish();
    });
    attachView(std::move(backButton));
}

void SignupActivity::createDialog() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    float width = 300;
    float height = 100;
    sf::Vector2f size(width, height);
    // sf::Vector2f position((windowSize - size) / 2.f);
    sf::Vector2f position(windowSize.x/2 - width/2, 200);
    sf::Vector2f spacing(0, height + 20);
    sf::Color color = sf::Color(150, 150, 150, 255);

    EditTextView::Ptr usrField = std::make_unique<EditTextView>(this, mFontManager.get(FontID::defaultFont), "Username", position, size);
    EditTextView::Ptr pwdField = std::make_unique<EditTextView>(this, mFontManager.get(FontID::defaultFont), "Password", spacing, size);
    EditTextView::Ptr rePwdField = std::make_unique<EditTextView>(this, mFontManager.get(FontID::defaultFont), "Re-Enter", spacing, size);
    TextView::Ptr errorView = std::make_unique<TextView>("", mFontManager.get(FontID::defaultFont), spacing, 20, sf::Color::Red);
    usrField->setLimit(10);
    pwdField->setLimit(10);
    rePwdField->setLimit(10);

    mUsername = usrField.get();
    mPassword = pwdField.get();
    mConfirmPassword = rePwdField.get();
    mError = errorView.get();

    ButtonView::Ptr submitButton = std::make_unique<ButtonView>(mFontManager.get(FontID::defaultFont), "Sign up", 20, sf::Vector2f(0, errorView->getCharacterSize() + 20), size, color);
    submitButton->setOnMouseButtonReleased(this, [&](EventListener* listener, const sf::Event& event) {
        checkSignup(mUsername->getText(), mPassword->getText(), mConfirmPassword->getText());
    });

    errorView->attachView(std::move(submitButton));
    rePwdField->attachView(std::move(errorView));
    pwdField->attachView(std::move(rePwdField));
    usrField->attachView(std::move(pwdField));
    attachView(std::move(usrField));
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

    UserData newUser(username, password, 0);
    userRepo.addUser(newUser);
    std::cout << " >> Signup success: " << username << std::endl;
    Intent::Ptr resIntent = Intent::Builder()
        .putExtra("username", username)
        .build();
    setResult((int)ResultCode::RESULT_OK, std::move(resIntent));
    finish();
}