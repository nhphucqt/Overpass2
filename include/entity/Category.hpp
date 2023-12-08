#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Entity/scene node category, used to dispatch commands
namespace Category {
	enum Type {
		None = 0,
		Player = 1 << 0,
		Lane = 1 << 1,
		Car = 1 << 2,
		Animal = 1 << 3,
		TrafficLight = 1 << 4,
		River = 1 << 5,
		Wood = 1 << 6,
		Crocodile = 1 << 7,
	};
}

#endif
