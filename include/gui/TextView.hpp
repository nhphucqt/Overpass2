#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <Viewable.hpp>
#include <SFML/Graphics.hpp>

class TextView: public Viewable {
private:
    sf::Font font;
    sf::Text text;

public:
    TextView(std::string text);

    void setText(std::string text);
    std::string getText();

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif