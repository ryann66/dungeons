#pragma once

#include "componentResource.hh"
#include "constants.h"
#include "itemResource.hh"
#include "position.hh"
#include "resource.hh"
#include "unitResource.hh"

#include <SDL3/SDL_rect.h>

#include <bitset>
#include <list>
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
using loader::componentResource;
using loader::itemResource;
using loader::resource;
using loader::unitResource;
using std::bitset;
using std::list;
using std::vector;

namespace game {

// NOTE: CENTER is valid in some contexts, or may be interpreted as any other value in cases where the absence of a
// cardinal direction is illogical
enum orientation { CENTER, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };

struct move_command {
	// movement
	orientation direction;
	float max_distance;

	// attack direction (NaN for no attack)
	float rotation;

	// items to use
	bitset<INVENTORY_SIZE> itemuse;
};

class entity;
class item;
class unit;
class weapon;
class component;
class interactable;
class effect;

class entity {
  private:
	bool kill = false;

  protected:
	bounds hitbox;

  public:
	entity(bounds hitbox) : hitbox(hitbox) {}

	entity(const resource* const res, float xpos, float ypos)
		: hitbox(bounds{.x1 = xpos - res->size.x / 2,
						.y1 = ypos - res->size.y / 2,
						.x2 = xpos + res->size.x / 2,
						.y2 = ypos + res->size.y / 2}) {}

	void killEntity() { kill = true; }

	bool isKilled() { return kill; }

	virtual void render() = 0;

	bounds& getBounds() { return hitbox; }
};

class item : public entity {
  public:
	item(const itemResource* const res, float xpos, float ypos) : imageResource(res), entity(res, xpos, ypos) {}

  private:
	const itemResource* const imageResource;

	int count;

  public:
	void render();

	void onUnitCollision(unit* collider) { killEntity(); }
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

	void move();

	float getRotation() { return rotation; }

	void onWeaponCollision(weapon* collider);

	void onUnitCollision(unit* collider);

	void onInteractableCollision(interactable* collider);

	virtual ~weapon();
};

class unit : public entity {
  public:
	unit(const unitResource* const res, float xpos, float ypos);

  private:
	const unitResource* const imageResource;

	enum orientation orientation;

	int health;

	bounds valid_loc;

  protected:
	item* primary;
	item* inventory[INVENTORY_SIZE];

  private:
	list<weapon*> summons;

	friend weapon::weapon(const itemResource* const, unit* const);
	friend weapon::~weapon();

  public:
	void render();

	void onWeaponCollision(weapon* collider);

	void onUnitCollision(unit* collider);

	void onComponentCollision(component* collider);

	void onInteractableCollision(interactable* collider);

	void move();

	// called on failed move (collision), brings the unit back to where it started
	void unmove() { hitbox = valid_loc; }

  protected:
	// subclass determines controls movement command (but can't move self)
	virtual move_command computeMove() = 0;

  public:
	virtual ~unit();
};

class component : entity {
  public:
	component(const componentResource* const res, float xpos, float ypos)
		: imageResource(res), entity(res, xpos, ypos) {}

  protected:
	const componentResource* const imageResource;

  public:
	void render();
};

class interactable : public component {
  private:
	int health;

  public:
	interactable(const componentResource* const res, float xpos, float ypos)
		: component(res, xpos, ypos), health(res->maxhealth) {}

	void onWeaponCollision(weapon* collider);
};

class effect : public entity {
  public:
	effect(bounds bounds) : entity(bounds) {}

	virtual void render() = 0;
};

} // namespace game
