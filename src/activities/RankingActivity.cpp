#include <RankingActivity.hpp>

#include <UserRepo.hpp>
#include <UserSession.hpp>

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
#include <SquareButtonFactory.hpp>

void RankingActivity::onLoadResources() {
    mFontManager.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureManager.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureManager.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureManager.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureManager.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureManager.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
    mTextureManager.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
    mTextureManager.load(TextureID::rankingTitleTexture, "res/textures/ui/Dialouge UI/dialog box small - editted.png");
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
    updateRanking();
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
        BackgroundFactory::create(this, mTextureManager.get(TextureID::mainMenuBackgroundTexture))
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
        this,
        mTextureManager.get(TextureID::settingMenuTexture),
        sf::Vector2f(0, 0),
        sf::Vector2f(122, 122) * 5.f,
        sf::IntRect(139, 12, 106, 122)
    );
    board->setPosition((windowSize - board->get().getGlobalBounds().getSize()) / 2.f + sf::Vector2f(0, 100));

    limitRanking = 6;
    barFontSize = 64;
    barSize = sf::Vector2f(board->get().getGlobalBounds().getSize().x - 60, 80);

    RectangleView::Ptr contentBarView = std::make_unique<RectangleView>(this, sf::Vector2f(barSize.x, barSize.y * (limitRanking+1)), sf::Vector2f(0, 0), sf::Color::Transparent);
    contentBarView->setPosition((board->get().getGlobalBounds().getSize().x - contentBarView->getGlobalBounds().getSize().x) / 2.f, 20);
    rankingView = contentBarView.get();

    sf::Vector2f rankingTitleSize;
    {
        sf::Texture& texture = mTextureManager.get(TextureID::rankingTitleTexture);
        rankingTitleSize = sf::Vector2f(texture.getSize()) * 2.f;
    }
    ButtonView::Ptr rankingTitleView = std::make_unique<ButtonView>(
        this,
        mTextureManager.get(TextureID::rankingTitleTexture),
        mFontManager.get(FontID::defaultFont),
        "Medium",
        48,
        sf::Vector2f(0, 0),
        rankingTitleSize
    );
    rankingTitleView->setPosition(10, -rankingTitleView->getGlobalBounds().getSize().y);
    rankingTitle = rankingTitleView.get();

    SpriteButtonView::Ptr prevButton = SquareButtonFactory::create(
        this, 
        mTextureManager.get(TextureID::squareButtonsTexture), 
        mFontManager.get(FontID::defaultFont), 
        "<", 
        sf::Vector2f(0, 0), 
        [&](EventListener* listener, const sf::Event& event) {
            currentGameMode = (currentGameMode - 1 + UserData::GameMode::GameModeCount) % UserData::GameMode::GameModeCount;
            updateRanking();
        }
    );
    SpriteButtonView::Ptr nextButton = SquareButtonFactory::create(
        this, 
        mTextureManager.get(TextureID::squareButtonsTexture), 
        mFontManager.get(FontID::defaultFont), 
        ">", 
        sf::Vector2f(0, 0), 
        [&](EventListener* listener, const sf::Event& event) {
            currentGameMode = (currentGameMode + 1) % UserData::GameMode::GameModeCount;
            updateRanking();
        }
    );
    nextButton->setPosition(0, prevButton->getGlobalBounds().getSize().y);
    prevButton->setPosition(board->get().getGlobalBounds().getSize().x, 10);

    prevButton->attachView(std::move(nextButton));


    board->attachView(std::move(contentBarView));
    board->attachView(std::move(rankingTitleView));
    board->attachView(std::move(prevButton));

    attachView(std::move(board));

    currentGameMode = (int)UserData::GameMode::easy;
    updateRanking();
}

void RankingActivity::updateRanking() {
    UserRepo::Leaderboard leaderboard = UserRepo::getInstance().getLeaderboard(UserData::GameMode(currentGameMode));
    
    rankingView->detachAllViews();

    rankingTitle->setText(UserData::gameModeNames[currentGameMode]);

    if (leaderboard.empty()) {
        TextView::Ptr emptyView = std::make_unique<TextView>(this, "No data", mFontManager.get(FontID::defaultFont), sf::Vector2f(0, 0), 64, sf::Color::White);
        emptyView->setPosition((rankingView->getGlobalBounds().getSize() - emptyView->getGlobalBounds().getSize()) / 2.f);
        rankingView->attachView(std::move(emptyView));
        return;
    }

    RectangleView::Ptr barView = RankingBarFactory::create(
        this,
        mFontManager.get(FontID::defaultFont),
        leaderboard.front().first,
        leaderboard.front().second,
        barSize,
        barFontSize
    );
    RectangleView* lastBar = barView.get();

    for (int i = 1; i < std::min(limitRanking, (int)leaderboard.size()); ++i) {
        RectangleView::Ptr tmpBarView = RankingBarFactory::create(
            this,
            mFontManager.get(FontID::defaultFont),
            leaderboard[i].first,
            leaderboard[i].second,
            barSize,
            barFontSize
        );
        tmpBarView->setPosition(sf::Vector2f(0, barSize.y));
        lastBar->attachView(std::move(tmpBarView));
        lastBar = (RectangleView*)lastBar->getViews().back().get();
    }

    RectangleView::Ptr underlineView = std::make_unique<RectangleView>(
        this,
        sf::Vector2f(rankingView->getGlobalBounds().getSize().x, 2),
        sf::Vector2f(0, rankingView->getGlobalBounds().getSize().y - barSize.y),
        sf::Color::White
    );

    UserSession& userSession = UserSession::getInstance();
    if (userSession.isLoggedin()) {
        UserData& userData = userSession.getCurrentUser();
        RectangleView::Ptr userBarView = RankingBarFactory::create(
            this,
            mFontManager.get(FontID::defaultFont),
            userData.getUsername(),
            userData.getHighscore(UserData::GameMode(currentGameMode)),
            barSize,
            barFontSize
        );
        userBarView->setPosition(0, rankingView->getGlobalBounds().getSize().y - barSize.y);
        rankingView->attachView(std::move(userBarView));
    }      

    rankingView->attachView(std::move(barView));
    rankingView->attachView(std::move(underlineView));
}