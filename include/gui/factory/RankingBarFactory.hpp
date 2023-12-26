#ifndef RANKING_BAR_FACTORY_HPP
#define RANKING_BAR_FACTORY_HPP

#include <UserData.hpp>
#include <SFML/Graphics.hpp>
#include <RectangleView.hpp>
#include <Activity.hpp>

class RankingBarFactory {
public:
    static RectangleView::Ptr create(Activity* context, sf::Font& font, std::string username, int score, sf::Vector2f size, int fontSize);
};


#endif