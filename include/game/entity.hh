#pragma once

#include "componentResource.hh"
#include "constants.h"
#include "itemResource.hh"
#include "position.hh"
#include "unitResource.hh"

#include <SDL3/SDL_rect.h>

#include <vector>

/*
 * This file contains classes for movable game entities and player items
 * entity: something that can be rendered in the game proper
 * item: something that can be held in an inventory
 * unit: something that moves around in the world independently
 * weapon: an item that is in entity form
 * component: a map object
 * interactable: a map object that can be hit (collided)
 * effect: a rendered animation
 */

using common::bounds;
using std::vector;

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
	// set to true for entity to be garbage collected at the end of the iteration
	bool kill = false;

	// renders this
	virtual void render() = 0;

	// tests if this collides with the bounding box
	virtual bool collides(bounds bounds) = 0;

	// optional behavior for when hit with a weapon
	virtual void onCollision(weapon* attacker) {};
};

class item {
  public:
	item(const itemResource* const res) : imageResource(res) {}

  private:
	const itemResource* const imageResource;

	int count;

  public:
	// called when item is used (might heal player, spawn a weapon, etc)
	virtual void onUse() {};
};

class weapon : public entity {
  public:
	weapon(const itemResource* const res, unit* const host);

  private:
	const itemResource* const imageResource;

	float xoff, yoff;
	float rotation;

	unit* const host;

  public:
	void render();

	virtual void move();

	const virtual bounds hitbox();

	virtual ~weapon();
};

class unit : public entity {
  public:
	unit(const unitResource* const res) : imageResource(res), health(res->maxhealth) {}

	// alternate ctor for filling inventory with a list of items
	unit(const unitResource* const res, vector<item*> items);

  private:
	float xpos, ypos;
	enum orientation orientation;

	const unitResource* const imageResource;

  protected:
	int health;

	item* primary;
	item* inventory[INVENTORY_SIZE];

  private:
	vector<weapon*> summons;
	friend weapon::~weapon();
	friend weapon::weapon(const itemResource* const, unit* const);

  public:
	void render();

	virtual bool collides(bounds bounds);

	// deals damage to the unit based on the weapon stats
	virtual void onCollision(weapon* attacker);

	// moves the unit
	void move();

	// subclass implementation of algorithm to determine intended movement direction
	virtual enum orientation computeMove() = 0;

	virtual ~unit();
};

class component {
  public:
	component(const componentResource* const res, int xpos, int ypos) : imageResource(res), xpos(xpos), ypos(ypos) {}

  protected:
	const int xpos, ypos;
	const componentResource* const imageResource;

  public:
	void render();

	virtual bool collides(bounds bounds);
};

class interactable : public component {
  protected:
	int health;

  public:
	interactable(const componentResource* const res, int xpos, int ypos)
		: component(res, xpos, ypos), health(res->maxhealth) {}

	virtual void onCollision(weapon* weapon) {}
};

class effect : public entity {
  public:
	void render() = 0;

	bool collides(bounds bounds) const {
		// effects never collide!
		return false;
	}
};

} // namespace game
