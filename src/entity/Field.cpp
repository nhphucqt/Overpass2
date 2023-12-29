#include <Field.hpp>
#include <AppConfig.hpp>
#include <RectangleView.hpp>

Field::Field(TextureManager *textures, bool isReverse):
Lane(textures->get(TextureID::Field), textures, isReverse) {
    type = Lane::Type::Field;
    textures->get(TextureID::Field).setRepeated(true);
    sprite.scale(4.f, 4.f);
	sf::IntRect textureRect(0, 0, 1400, 32);
    sprite.setTextureRect(textureRect);
    buildLane();

}

void Field::updateCurrent(sf::Time dt) {
    // currently update nothing because bushes don't move
}

void Field::buildLane() {
    sf::Vector2f cellSize = AppConfig::getInstance().get<sf::Vector2f>(ConfigKey::CellSize);
    std::unique_ptr<Green> tree(new Green(Green::Tree, *laneTextures));
    std::unique_ptr<Green> bush(new Green(Green::Bush, *laneTextures));
    std::unique_ptr<Green> circleBush(new Green(Green::CircleBush, *laneTextures));
    greens.push_back(tree.get());
    greens.push_back(bush.get());
    greens.push_back(circleBush.get());
    tree->setPosition(cellSize.x * 3, 0);
    bush->setPosition(cellSize.x * 6, 0);
    circleBush->setPosition(cellSize.x * 9, 0);
    this->attachView(std::move(tree));
    this->attachView(std::move(bush));
    this->attachView(std::move(circleBush));
}
