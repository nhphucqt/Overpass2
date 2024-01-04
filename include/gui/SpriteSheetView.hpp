#ifndef SPRITE_SHEET_VIEW_HPP
#define SPRITE_SHEET_VIEW_HPP

#include <ViewGroup.hpp>

class SpriteSheetView: public ViewGroup {
private:
    sf::Sprite mSprite;
    sf::IntRect mTextureRect;
    int mColumns;
    int mRows;
    int mCurrentFrame;
    int mFrameCount;
    sf::Time mFrameTime;
    sf::Time mElapsedTime;

public:
    SpriteSheetView(EventPublisher* publisher, const sf::Texture& texture, int columns, int rows, sf::Time frameTime);
    SpriteSheetView(EventPublisher* publisher, const sf::Texture& texture, int columns, int rows, sf::Time frameTime, const sf::Vector2f& position);
    SpriteSheetView(EventPublisher* publisher, const sf::Texture& texture, int columns, int rows, sf::Time frameTime, const sf::Vector2f& position, const sf::Vector2f& size);

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    virtual void updateCurrent(sf::Time delta) override;
    void goToNextFrame();
};

#endif