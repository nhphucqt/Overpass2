#include <RankingActivity.hpp>

#include <UserRepo.hpp>

#include <AppConfig.hpp>
#include <ButtonView.hpp>
#include <TextView.hpp>

#include <ActivityFactory.hpp>
#include <SettingsActivity.hpp>
#include <ProfileActivity.hpp>
#include <HelpActivity.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>
#include <RankingBarFactory.hpp>

void RankingActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
    mTextureManager.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
}

void RankingActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createBoard();
}

void RankingActivity::onAttach() {
    // ...
}

void RankingActivity::onResume() {
    // ...
}

void RankingActivity::onPause() {
    // ...
}

void RankingActivity::onDestroy() {
    // ...
}

void RankingActivity::onEvent(const sf::Event& event) {
    // ...
}

void RankingActivity::updateCurrent(sf::Time dt) {
    // ...
}

void RankingActivity::onActivityResult(int requestCode, int resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_TITLEBAR_BUTTONS) {
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

void RankingActivity::createBackground() {
    attachView(
        BackgroundFactory::create(mTextureManager.get(TextureID::mainMenuBackgroundTexture))
    );
}

void RankingActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureManager,
            mFontManager.get(FontID::defaultFont),
            "Ranking",
            TitlebarFactory::TitlebarType::NONE,
            REQUEST_TITLEBAR_BUTTONS
        )
    );
}

void RankingActivity::createBackButton() {
    attachView(
        BackButtonFactory::create(
            this,
            mTextureManager.get(TextureID::squareButtonsTexture),
            mFontManager.get(FontID::defaultFont)
        )
    );
}

void RankingActivity::createBoard() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    SpriteView::Ptr board = std::make_unique<SpriteView>(
        mTextureManager.get(TextureID::settingMenuTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(122, 122) * 5.f,
        sf::IntRect(139, 12, 106, 122)
    );
    board->setPosition((windowSize - board->get().getGlobalBounds().getSize()) / 2.f + sf::Vector2f(0, 100));

    UserRepo::Leaderboard leaderboard = UserRepo::getInstance().getLeaderboard();

    if (leaderboard.empty()) {
        TextView::Ptr emptyView = std::make_unique<TextView>("No data", mFontManager.get(FontID::defaultFont), sf::Vector2f(0, 0), 64, sf::Color::White);
        emptyView->setPosition((board->get().getGlobalBounds().getSize() - emptyView->getGlobalBounds().getSize()) / 2.f);
        board->attachView(std::move(emptyView));
        attachView(std::move(board));
        return;
    }

    int limit = 7;
    int fontSize = 64;
    sf::Vector2f size(board->get().getGlobalBounds().getSize().x - 60, 80);

    RectangleView::Ptr barView = RankingBarFactory::create(
        this,
        mFontManager.get(FontID::defaultFont),
        leaderboard.front().first,
        leaderboard.front().second,
        size,
        fontSize
    );
    barView->setPosition(sf::Vector2f((board->get().getGlobalBounds().getSize().x - barView->getGlobalBounds().getSize().x) / 2.f, 20));
    RectangleView* lastBar = barView.get();

    for (int i = 1; i < std::min(limit, (int)leaderboard.size()); ++i) {
        RectangleView::Ptr tmpBarView = RankingBarFactory::create(
            this,
            mFontManager.get(FontID::defaultFont),
            leaderboard[i].first,
            leaderboard[i].second,
            size,
            fontSize
        );
        tmpBarView->setPosition(sf::Vector2f(0, size.y));
        lastBar->attachView(std::move(tmpBarView));
        lastBar = (RectangleView*)lastBar->getViews().back().get();
    }

    board->attachView(std::move(barView));

    attachView(std::move(board));
}