#include <SpriteSheetView.hpp>

SpriteSheetView::SpriteSheetView(EventPublisher* publisher, const sf::Texture& texture, int columns, int rows, sf::Time frameTime)
: SpriteSheetView(publisher, texture, columns, rows, frameTime, sf::Vector2f(0, 0), sf::Vector2f(0, 0)) {
}

SpriteSheetView::SpriteSheetView(EventPublisher* publisher, const sf::Texture& texture, int columns, int rows, sf::Time frameTime, const sf::Vector2f& position)
: SpriteSheetView(publisher, texture, columns, rows, frameTime, position, sf::Vector2f(0, 0)) {
}

SpriteSheetView::SpriteSheetView(EventPublisher* publisher, const sf::Texture& texture, int columns, int rows, sf::Time frameTime, const sf::Vector2f& position, const sf::Vector2f& size)
: ViewGroup(publisher), mSprite(texture), mTextureRect(0, 0, texture.getSize().x / columns, texture.getSize().y / rows), mColumns(columns), mRows(rows), mCurrentFrame(0), mFrameCount(columns * rows), mFrameTime(frameTime), mElapsedTime(sf::Time::Zero) {
    setPosition(position);
    mSprite.setTextureRect(mTextureRect);
    mSprite.setScale(size.x / mTextureRect.width, size.y / mTextureRect.height);
}

void SpriteSheetView::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void SpriteSheetView::updateCurrent(sf::Time dt) {
    mElapsedTime += dt;
    if (mElapsedTime >= mFrameTime) {
        mElapsedTime -= mFrameTime;
        goToNextFrame();
    }
}

void SpriteSheetView::goToNextFrame() {
    mCurrentFrame = (mCurrentFrame + 1) % mFrameCount;
    mTextureRect.left = (mCurrentFrame % mColumns) * mTextureRect.width;
    mTextureRect.top = (mCurrentFrame / mColumns) * mTextureRect.height;
    mSprite.setTextureRect(mTextureRect);
}