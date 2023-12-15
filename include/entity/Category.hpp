#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Entity/scene node category, used to dispatch commands
namespace Category {
	enum Type {
		None = 0,
		Player = 1 << 0,
		Lane = 1 << 1,
		Car = 1 << 2,
		Train = 1 << 3,
		Animal = 1 << 4,
		TrafficLight = 1 << 5,
		River = 1 << 6,
		Wood = 1 << 7,
		Crocodile = 1 << 8,
		Green = 1 << 9,
	};
}

#endif
