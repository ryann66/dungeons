#include "entity.hh"
#include "constants.h"
#include "main.hh"
#include "resource.hh"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdexcept>

namespace game {

void item::render() {
	SDL_FRect rect{.x = hitbox.x1, .y = hitbox.y1, .w = hitbox.x2 - hitbox.x1, .h = hitbox.y2 - hitbox.y1};
	SDL_RenderTexture(renderer, imageResource->texture, NULL, &rect);
}

weapon::weapon(const itemResource* const res, unit* const host, int strength, int damage)
	: imageResource(res), host(host), strength(strength), damage(damage), entity(bounds{
																			  .x1 = 0,
																			  .y1 = 0,
																			  .x2 = res->size.x,
																			  .y2 = res->size.y,
																		  }) {
	host->summons.push_back(this);
	host->movelocked = true;
}

void weapon::render() {
	SDL_FRect rect{
		.x = host->hitbox.x1 + host->imageResource->attach.x - imageResource->origin.x,
		.y = host->hitbox.y1 + host->imageResource->attach.y - imageResource->origin.y,
		.w = host->hitbox.x1 + host->imageResource->attach.x - imageResource->origin.x + hitbox.x2 - hitbox.x1,
		.h = host->hitbox.y1 + host->imageResource->attach.y - imageResource->origin.y + hitbox.y2 - hitbox.y1};
	SDL_FPoint org{.x = hitbox.x1 + xoff, .y = hitbox.y1 + yoff};
	SDL_RenderTextureRotated(renderer, imageResource->texture, NULL, &rect, rotation, &org, SDL_FLIP_NONE);
}

void weapon::move() {
	// move

	// if finished, kill
}

void weapon::onWeaponCollision(weapon* collider) {
	this->strength -= (collider->strength + collider->imageResource->weight);
	if (this->strength <= 0)
		killEntity();
}

void weapon::onUnitCollision(unit* collider) {
	this->strength -= collider->imageResource->weight;
	if (this->strength <= 0)
		killEntity();
}

void weapon::onInteractableCollision(interactable* collider) {
	this->strength -= collider->imageResource->weight;
	if (this->strength <= 0)
		killEntity();
}

weapon::~weapon() {
	host->movelocked = false;
	for (auto it = host->summons.begin(); it != host->summons.end(); it++) {
		if (*it == this) {
			host->summons.erase(it);
			return;
		}
	}
	// unreachable?
	while (true)
		;
}

unit::unit(const unitResource* const res, float xpos, float ypos)
	: imageResource(res), health(res->maxhealth), entity(res, xpos, ypos), primary(nullptr),
	  valid_loc({.x1 = 0, .y1 = 0, .x2 = res->size.x, .y2 = res->size.y}), orientation(NORTH) {
	int iidx = 0, pidx = -1;
	for (const itemResource* it : res->items) {
		inventory[iidx] = it;
		if (it->type == loader::SWORD && pidx == -1)
			pidx = iidx;
		if (++iidx == INVENTORY_SIZE)
			break;
	}
	for (; iidx < INVENTORY_SIZE; iidx++)
		inventory[iidx] = nullptr;
	if (pidx != -1) {
		equip(pidx);
	}
}

void unit::render() {
	SDL_Texture* text;
	switch (orientation) {
	default:
	case NORTH:
		text = imageResource->textures[0];
		break;
	case NORTHEAST:
		text = imageResource->textures[1];
		break;
	case EAST:
		text = imageResource->textures[2];
		break;
	case SOUTHEAST:
		text = imageResource->textures[3];
		break;
	case SOUTH:
		text = imageResource->textures[4];
		break;
	case SOUTHWEST:
		text = imageResource->textures[5];
		break;
	case WEST:
		text = imageResource->textures[6];
		break;
	case NORTHWEST:
		text = imageResource->textures[7];
		break;
	}

	SDL_FRect rect{.x = hitbox.x1, .y = hitbox.y1, .w = hitbox.x2 - hitbox.x1, .h = hitbox.y2 - hitbox.y1};
	SDL_RenderTexture(renderer, text, NULL, &rect);
}

void unit::onWeaponCollision(weapon* collider) {
	health -= collider->damage;
}

void unit::onUnitCollision(unit* collider) {}

void unit::onComponentCollision(component* collider) {}

void unit::onInteractableCollision(interactable* collider) {}

void unit::move() {
	// check for expired stats

	// check movelock
	if (movelocked)
		return;

	// move

	// attack/use item
}

void unit::equip(int iidx) {
	if (movelocked)
		return;

	if (iidx < 0 || iidx >= INVENTORY_SIZE) {
		throw new std::invalid_argument("Inventory index out of bounds");
	}

	// check is weapon (or equipment in later versions)
	const itemResource* res = inventory[iidx];
	if (res->type != loader::SWORD) {
		// adjust stats
		strength -= primary->strength;
		strength += res->strength;
		damage -= primary->damage;
		damage += res->damage;
		regen -= primary->regen;
		regen += res->regen;
		speed -= primary->walkspeed;
		speed += res->walkspeed;

		maxhealth -= primary->health;
		maxhealth += res->health;
		health = std::min(maxhealth, health);
	} else {
		throw new std::invalid_argument("Inventory slot is not equippable");
	}
}

unit::~unit() {
	while (!summons.empty()) {
		// summons should remove themselves when deleted!
		delete summons.front();
	}
}

void component::render() {
	SDL_FRect rect{.x = hitbox.x1, .y = hitbox.y1, .w = hitbox.x2 - hitbox.x1, .h = hitbox.y2 - hitbox.y1};
	SDL_RenderTexture(renderer, imageResource->texture, NULL, &rect);
}

void interactable::onWeaponCollision(weapon* collider) {
	health -= collider->damage;
	if (health <= 0)
		killEntity();
}

} // namespace game