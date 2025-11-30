#pragma once

#include "effect.hh"
#include "entitity.hh"

#include <vector>

using std::vector;

namespace game {

struct dungeon {
	vector<entity*> units;
	vector<entity*> temporary;

	vector<component*> nonblocking;
	vector<interactable*> blocking;

	vector<effect*> effects;
};

} // namespace game