#include <River.hpp>

River::River(TextureManager* textures): riverTexture(textures) {
	sf::IntRect textureRect(0, 0, 1400, 150);
    sprite.setTexture(textures->get(TextureID::River));
    sprite.setTextureRect(textureRect);
    loadTextures();
    buildRiver();
}

void River::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

void River::loadTextures() {
    riverTexture->load(TextureID::Wood, "res/textures/Wood.jpg");
}

void River::updateCurrent(sf::Time dt) {
    Log* lastLog = logs[logs.size() - 1];
    Log* firstLog = logs[0];
    int distance = 1400/logs.size();
    if (lastLog->getPosition().x > 1600)
        logs[logs.size() - 1]->setPosition(firstLog->getPosition().x - 450 - distance, lastLog->getPosition().y);
}

void River::buildRiver() {
    std::unique_ptr<Log> log(new Log(Log::Wood, *riverTexture));
    logs.push_back(log.get());
    log->setPosition(0.f, 75.f);
    log->setVelocity(150.f, 0.f);
    this->attachView(std::move(log));
}