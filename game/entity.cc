#include "entity.hh"
#include "constants.h"
#include "resource.hh"

namespace game {

void item::render() {
	// TODO
}

weapon::weapon(const itemResource* const res, unit* const host, int strength, int damage)
	: imageResource(res), host(host), strength(strength), damage(damage),
	  entity(bounds{
		  .x1 = host->getBounds().x1 + host->imageResource->attach.x - res->origin.x,
		  .y1 = host->getBounds().y1 + host->imageResource->attach.y - res->origin.y,
		  .x2 = host->getBounds().x1 + host->imageResource->attach.x - res->origin.x + res->size.x,
		  .y2 = host->getBounds().y1 + host->imageResource->attach.y - res->origin.y + res->size.y,
	  }) {
	host->summons.push_back(this);
}

void weapon::render() {
	// TODO
}

void weapon::move() {
	// TODO
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
	int iidx = 0;
	for (const itemResource* it : res->items) {
		if (it->type == loader::SWORD && primary == nullptr)
			primary = it;
		else {
			inventory[iidx++] = it;
			if (iidx == INVENTORY_SIZE)
				break;
		}
	}
	for (; iidx < INVENTORY_SIZE; iidx++)
		inventory[iidx] = nullptr;
}

void unit::render() {
	// TODO
}

void unit::onWeaponCollision(weapon* collider) {
	health -= collider->damage;
}

void unit::onUnitCollision(unit* collider) {}

void unit::onComponentCollision(component* collider) {}

void unit::onInteractableCollision(interactable* collider) {}

void unit::move() {
	// TODO
}

unit::~unit() {
	while (!summons.empty()) {
		// summons should remove themselves when deleted!
		delete summons.front();
	}
}

void component::render() {
	// TODO
}

void interactable::onWeaponCollision(weapon* collider) {
	health -= collider->damage;
	if (health <= 0)
		killEntity();
}

} // namespace game