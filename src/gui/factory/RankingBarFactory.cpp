#include <RankingBarFactory.hpp>

#include <UserData.hpp>
#include <SFML/Graphics.hpp>
#include <RectangleView.hpp>
#include <TextView.hpp>
#include <Activity.hpp>


RectangleView::Ptr RankingBarFactory::create(Activity* context, sf::Font& font, std::string username, int score, sf::Vector2f size, int fontSize) {
    RectangleView::Ptr barView = std::make_unique<RectangleView>(context, size, sf::Vector2f(0, 0), sf::Color::Transparent);
    
    TextView::Ptr usernameView = std::make_unique<TextView>(context, username, font, sf::Vector2f(0, 0), fontSize, sf::Color::White);
    usernameView->setPosition(sf::Vector2f(10, (size.y - usernameView->getGlobalBounds().getSize().y) / 2.f));

    TextView::Ptr scoreView = std::make_unique<TextView>(context, std::to_string(score), font, sf::Vector2f(0, 0), fontSize, sf::Color::White);
    scoreView->setPosition(sf::Vector2f(size.x - scoreView->getGlobalBounds().getSize().x - 10, (size.y - scoreView->getGlobalBounds().getSize().y) / 2.f));

    barView->setOnMouseMoved([&](EventListener* listener, const sf::Event& event) {
        RectangleView* barView = dynamic_cast<RectangleView*>(listener);
        if (barView->isMouseHovering(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
            barView->setFillColor(sf::Color(0, 0, 0, 50));
        else
            barView->setFillColor(sf::Color::Transparent);
    });



    barView->attachView(std::move(usernameView));
    barView->attachView(std::move(scoreView));
    return std::move(barView);
}
