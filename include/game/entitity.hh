#pragma once

#include "componentResource.hh"
#include "constants.h"
#include "effectResource.hh"
#include "entityResource.hh"
#include "itemResource.hh"
#include "position.hh"

#include <SDL3/SDL_rect.h>

/*
 * This file contains classes for movable game entities and player items
 * entity: something that can be rendered in the game proper
 * item: something that can be held in an inventory
 * unit: something that moves around in the world independently
 * weapon: an item that is in entity form
 * component: a map object
 * interactable: a map object that can be hit (collided)
 */

using common::bounds;

namespace game {

// NOTE: CENTER is valid in some contexts, or may be interpreted as any other value in cases where the absence of a
// cardinal direction is illogical
enum orientation { CENTER, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };

class entity;
class item;
class unit;
class weapon;
class component;
class interactable;
class effect;

class entity {
  public:
	// renders this
	virtual void render() = 0;

	// tests if this collides with the bounding box
	virtual bool collides(bounds bounds) = 0;

	// optional behavior for when hit with a weapon
	virtual void onCollision(weapon* attacker) {};
};

class item {
	const itemResource* const imageResource;
	const int unitWeight, stackSize;

	int count;

	inline int weight() const { return count * unitWeight; }

	// called when item is used (might heal player, spawn a weapon, etc)
	virtual void onUse() {};
};

class unit : public entity {
	float xpos, ypos;
	orientation orientation;

	const entityResource* const imageResource;

	int health;
	int weight;
	int strength;

	item* primary;
	item* offhand;

	item* inventory[INVENTORY_SIZE];

	virtual void render();

	virtual bool collides(bounds bounds);

	// deals damage to the unit based on the weapon stats
	virtual void onCollision(weapon* attacker);

	// moves the unit
	virtual void move();

	// subclass implementation of algorithm to determine intended movement direction
	virtual enum orientation computeMove();
};

class weapon : public entity {
	const item* const item;

	float xoff, yoff;
	float rotation;

	entity* host;

	virtual void render();

	virtual void move();

	const virtual bounds bounds();
};

class component {
	const int xpos, ypos, width, height;
	const componentResource* const imageResource;

	virtual void render();

	virtual bool collides(bounds bounds);

	virtual void onCollision(weapon weapon);
};

class interactable : public component {
	virtual void onCollision(weapon weapon) = 0;
};

class effect : public entity {
	const effectResource* const imageResource;

	virtual void render();

	virtual bool collides(bounds bounds) const {
		// effects never collide!
		return false;
	}
};

} // namespace game
