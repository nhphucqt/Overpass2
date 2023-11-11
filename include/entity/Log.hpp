#ifndef LOG_HPP
#define LOG_HPP
#include <Entity.hpp>

// the only entity that is not destroyed in river
class Log: public Entity {
    public:
        enum class LogType {Harmful, Harmless}; // crocodile is a harmful log
        Log(sf::Texture texture, LogType log = LogType::Harmless);
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        LogType getLogType();
    private:
        const EntityType TYPE = EntityType::Log;
        LogType logType;
};

#endif