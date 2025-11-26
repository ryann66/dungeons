#pragma once

#include "component.hh"
#include "effect.hh"
#include "entitity.hh"

#include <vector>

using std::vector;

namespace game {

struct dungeon {
	vector<entity*> units;
	vector<entity*> temporary;

	vector<component*> nonblocking;
	vector<component*> blocking;

	vector<effect*> effects;
};

} // namespace game