#pragma once

#include "entity.hh"

#include <vector>

using std::vector;

namespace game {

struct dungeon {
	// units are given failable movement windows and tested for collision by weapons, units, components, and
	// interactables
	vector<unit*> units;

	// weapons are given movement windows and tested for collision with weapons, units, and interactables
	vector<weapon*> weapons;

	// items are tested for collision by units (default collision handler)
	vector<item*> items;

	// nonblocking components are never tested for collision
	vector<component*> nonblocking;

	// blocking components are are never tested for collision
	vector<component*> blocking;

	// interactable components are tested for collision by weapons
	vector<interactable*> dynamic;

	// effects are given movement windows but never tested for collision
	vector<effect*> effects;
};

} // namespace game