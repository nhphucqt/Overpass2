#include <RankingActivity.hpp>

#include <UserRepo.hpp>
#include <UserSession.hpp>

#include <AppConfig.hpp>
#include <ButtonView.hpp>
#include <TextView.hpp>

#include <ActivityProfile.hpp>

#include <TitlebarFactory.hpp>
#include <BackgroundFactory.hpp>
#include <BackButtonFactory.hpp>
#include <RankingBarFactory.hpp>
#include <SquareButtonFactory.hpp>

void RankingActivity::onLoadResources() {
    mFontHolder.load(FontID::defaultFont, "res/fonts/retro-pixel-thick.ttf");
    mTextureHolder.load(TextureID::mainMenuBackgroundTexture, "res/textures/bg/sprout-valley.png");
    mTextureHolder.load(TextureID::titleBackgroundTexture, "res/textures/ui/Dialouge UI/Premade dialog box small reversed.png");
    mTextureHolder.load(TextureID::characterTitleBarTexture, "res/textures/ui/Dialouge UI/Emotes/idle-emote.png");
    mTextureHolder.load(TextureID::squareButtonsTexture, "res/textures/ui/buttons/Square Buttons 26x26.png");
    mTextureHolder.load(TextureID::iconsTexture, "res/textures/ui/Icons/white icons.png");
    mTextureHolder.load(TextureID::settingMenuTexture, "res/textures/ui/Setting menu.png");
    mTextureHolder.load(TextureID::rankingTitleTexture, "res/textures/ui/Dialouge UI/dialog box small - editted.png");
}

void RankingActivity::onCreate() {
    createBackground();
    createTitle();
    createBackButton();
    createBoard();
}

void RankingActivity::onActivityResult(int requestCode, ResultCode resultCode, Intent::Ptr data) {
    if (requestCode == REQUEST_TITLEBAR_BUTTONS) {
        if (resultCode == ResultCode::RESULT_OK) {
            int titleType = data->getExtra<int>("titleType", -1);
            if (titleType == -1) {
                return;
            }
            Intent::Ptr intent = Intent::Builder()
                .setRequestCode(REQUEST_TITLEBAR_BUTTONS)
                .build();
            if (titleType == (int)TitlebarFactory::TitlebarType::SETTINGS) {
                startActivity(ActivityID::Settings, std::move(intent));
            } else if (titleType == (int)TitlebarFactory::TitlebarType::HELP) {
                startActivity(ActivityID::Help, std::move(intent));
            } else if (titleType == (int)TitlebarFactory::TitlebarType::PROFILE) {
                startActivity(ActivityID::Profile, std::move(intent));
            }
        }
    }
}

void RankingActivity::createBackground() {
    attachView(
        BackgroundFactory::create(this, mTextureHolder.get(TextureID::mainMenuBackgroundTexture))
    );
}

void RankingActivity::createTitle() {
    attachView(
        TitlebarFactory::create(
            this,
            mTextureHolder,
            mFontHolder.get(FontID::defaultFont),
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
            mTextureHolder.get(TextureID::squareButtonsTexture),
            mFontHolder.get(FontID::defaultFont)
        )
    );
}

void RankingActivity::createBoard() {
    AppConfig& config = AppConfig::getInstance();
    sf::Vector2f windowSize = config.get<sf::Vector2f>(ConfigKey::WindowSize);

    SpriteView::Ptr board = std::make_unique<SpriteView>(
        this,
        mTextureHolder.get(TextureID::settingMenuTexture),
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
        sf::Texture& texture = mTextureHolder.get(TextureID::rankingTitleTexture);
        rankingTitleSize = sf::Vector2f(texture.getSize()) * 2.f;
    }
    ButtonView::Ptr rankingTitleView = std::make_unique<ButtonView>(
        this,
        mTextureHolder.get(TextureID::rankingTitleTexture),
        mFontHolder.get(FontID::defaultFont),
        "",
        48,
        sf::Vector2f(0, 0),
        rankingTitleSize
    );
    rankingTitleView->setPosition(10, -rankingTitleView->getGlobalBounds().getSize().y);
    rankingTitle = rankingTitleView.get();

    SpriteButtonView::Ptr prevButton = SquareButtonFactory::create(
        this, 
        mTextureHolder.get(TextureID::squareButtonsTexture), 
        mFontHolder.get(FontID::defaultFont), 
        "<", 
        sf::Vector2f(0, 0), 
        [&](EventListener* listener, const sf::Event& event) {
            currentGameMode = (currentGameMode - 1 + (int)UserData::GameMode::GameModeCount) % (int)UserData::GameMode::GameModeCount;
            updateRanking();
        }
    );
    SpriteButtonView::Ptr nextButton = SquareButtonFactory::create(
        this, 
        mTextureHolder.get(TextureID::squareButtonsTexture), 
        mFontHolder.get(FontID::defaultFont), 
        ">", 
        sf::Vector2f(0, 0), 
        [&](EventListener* listener, const sf::Event& event) {
            currentGameMode = (currentGameMode + 1) % (int)UserData::GameMode::GameModeCount;
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
        TextView::Ptr emptyView = std::make_unique<TextView>(this, "No data", mFontHolder.get(FontID::defaultFont), sf::Vector2f(0, 0), 64, sf::Color::White);
        emptyView->setPosition((rankingView->getGlobalBounds().getSize() - emptyView->getGlobalBounds().getSize()) / 2.f);
        rankingView->attachView(std::move(emptyView));
        return;
    }

    RectangleView::Ptr barView = RankingBarFactory::create(
        this,
        mFontHolder.get(FontID::defaultFont),
        leaderboard.front().first,
        leaderboard.front().second,
        barSize,
        barFontSize
    );
    RectangleView* lastBar = barView.get();

    for (int i = 1; i < std::min(limitRanking, (int)leaderboard.size()); ++i) {
        RectangleView::Ptr tmpBarView = RankingBarFactory::create(
            this,
            mFontHolder.get(FontID::defaultFont),
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
            mFontHolder.get(FontID::defaultFont),
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