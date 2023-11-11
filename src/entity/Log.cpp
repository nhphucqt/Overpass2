#include <Log.hpp>

Log::Log(sf::Texture texture, LogType log): Entity(texture), logType(log) {}

Log::LogType Log::getLogType() {
    return logType;
}

void Log::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}