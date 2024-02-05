#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Entity/scene node category, used to dispatch commands
namespace ViewCategory {
	enum Type {
		None      = 0,
		Player_1  = 1 << 0,
		Player_2  = 1 << 1,
		Lane      = 1 << 2,
		River     = 1 << 3,
		Vehicle   = 1 << 4,
		Train     = 1 << 5,
		Animal    = 1 << 6,
		Log       = 1 << 7,
		Crocodile = 1 << 8,
		Green     = 1 << 9,
	};
}

#endif