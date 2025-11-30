#pragma once

#include "effect.hh"
#include "entitity.hh"

#include <vector>

using std::vector;

namespace game {

struct dungeon {
	// units are given movement windows and tested for collision by weapons
	vector<unit*> units;

	// weapons are given movement windows and tested for collision with other weapons
	vector<weapon*> weapons;

	// nonblocking components are never tested for collision
	vector<component*> nonblocking;

	// blocking components are tested for collision by units, but not weapons
	vector<component*> blocking;

	// interactable components are tested for collision by units and weapons
	vector<interactable*> interactable;

	// effects are given movement but not tested for collision
	vector<effect*> effects;
};

} // namespace game