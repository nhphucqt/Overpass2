#include <Animation.hpp>
#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

Animation::Animation()
: mSprite(), mFrameSize(), mNumFrames(0), mCurrentFrame(0), mDuration(sf::Time::Zero), mElapsedTime(sf::Time::Zero), mRepeat(false)
{}

Animation::Animation(const sf::Texture &texture)
	: mSprite(texture), mFrameSize(), mNumFrames(0), mCurrentFrame(0), mDuration(sf::Time::Zero), mElapsedTime(sf::Time::Zero), mRepeat(false)
{}

void Animation::setTexture(const sf::Texture &texture) {
	mSprite.setTexture(texture);
}

const sf::Texture *Animation::getTexture() const {
	return mSprite.getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize) {
	mFrameSize = frameSize;
}

sf::Vector2i Animation::getFrameSize() const {
	return mFrameSize;
}

void Animation::setNumFrames(std::size_t numFrames) {
	mNumFrames = numFrames;
}

std::size_t Animation::getNumFrames() const {
	return mNumFrames;
}

void Animation::setDuration(sf::Time duration) {
	mDuration = duration;
}

void Animation::setDuration(float duration) {
	mDuration = sf::seconds(duration);
}

sf::Time Animation::getDuration() const {
	return mDuration;
}

void Animation::setRepeating(bool flag) {
	mRepeat = flag;
}

bool Animation::isRepeating() const {
	return mRepeat;
}

void Animation::restart() {
	mCurrentFrame = 0;
	mElapsedTime = sf::Time::Zero;
}

bool Animation::isFinished() const {
	return mCurrentFrame >= mNumFrames;
}

sf::FloatRect Animation::getLocalBounds() const {
	return sf::FloatRect(sf::Vector2f(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Animation::getGlobalBounds() const {
	return getTransform().transformRect(getLocalBounds());
}

void Animation::update(sf::Time dt) {
	sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
	mElapsedTime += dt;


	if (mElapsedTime >= timePerFrame) {
		mElapsedTime -= timePerFrame;
		if (mRepeat) {
			mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;
		} else {
			mCurrentFrame = std::min(mCurrentFrame + 1, mNumFrames-1);
		}
	}

	sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
	int numCol = textureBounds.x / mFrameSize.x;
	int x = mCurrentFrame % numCol;
	int y = mCurrentFrame / numCol;
	sf::IntRect textureRect(x * mFrameSize.x, y * mFrameSize.y, mFrameSize.x, mFrameSize.y);

	mSprite.setTextureRect(textureRect);
}

void Animation::reverseSprite() {
	mSprite.setScale(-1.f, 1.f);
	mSprite.setOrigin(mFrameSize.x, 0.f);
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

Animation::AnimationData Animation::serialize() const {
	AnimationData data;
	data.frameSizeX = mFrameSize.x;
	data.frameSizeY = mFrameSize.y;
	data.numFrames = mNumFrames;
	data.currentFrame = mCurrentFrame;
	data.duration = mDuration.asSeconds();
	data.elapsedTime = mElapsedTime.asSeconds();
	data.repeat = mRepeat;
	return data;
}

void Animation::deserialize(const AnimationData &data) {
	mFrameSize.x = data.frameSizeX;
	mFrameSize.y = data.frameSizeY;
	mNumFrames = data.numFrames;
	mCurrentFrame = data.currentFrame;
	mDuration = sf::seconds(data.duration);
	mElapsedTime = sf::seconds(data.elapsedTime);
	mRepeat = data.repeat;

	sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
	int numCol = textureBounds.x / mFrameSize.x;
	int x = mCurrentFrame % numCol;
	int y = mCurrentFrame / numCol;
	sf::IntRect textureRect(x * mFrameSize.x, y * mFrameSize.y, mFrameSize.x, mFrameSize.y);

	mSprite.setTextureRect(textureRect);
}