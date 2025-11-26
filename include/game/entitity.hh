#pragma once

#include "constants.h"
#include "entityResource.hh"
#include "itemResource.hh"

/*
 * This file contains classes for movable game entities and player items
 * entity: something that can be rendered in the game proper
 * item: something that can be held in an inventory
 * unit: something that moves around in the world independently
 * itemEntity: an item that is in entity form
 */

namespace game {

enum orientation { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };

class entity {};

class item {
	const itemResource* const imageResource;
	const int unitWeight, stackSize;

	int count;

	inline int weight() const { return count * unitWeight; }
};

class unit : public entity {
	float xpos, ypos;
	orientation orientation;

	const entityResource* const imageResource;
	const int max_health, max_weight;

	int health;
	int weight;
	int strength;

	item* primary;
	item* offhand;

	item* inventory[INVENTORY_SIZE];
};

class itemEntity : public entity {
	const item* const item;

	float xoff, yoff;
	float rotation;

	entity* host;
};

} // namespace game
