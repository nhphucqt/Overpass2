#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Entity/scene node category, used to dispatch commands
namespace Category {
	enum Type {
		None = 0,
		Player = 1 << 0,
		Lane = 1 << 1,
		River = 1 << 2,
		Vehicle = 1 << 3,
		Train = 1 << 4,
		Animal = 1 << 5,
		Log = 1 << 6,
		Crocodile = 1 << 7,
		Green = 1 << 8,
	};
}

#endif