#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <functional>
#include <cassert>

#include <SFML/System/Time.hpp>

#include <ViewCategory.hpp>

class ViewGroup;

struct Command {
	Command();

	std::function<void(ViewGroup &, sf::Time)> action;
	unsigned int category;
	bool isUsed;
};

template <typename GameObject, typename Function>
std::function<void(ViewGroup &, sf::Time)> derivedAction(Function fn) {
	return [=](ViewGroup &node, sf::Time dt) {
		// Check if cast is safe
		assert(dynamic_cast<GameObject *>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject &>(node), dt);
	};
}

#endif
