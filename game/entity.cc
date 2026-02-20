#include "entity.hh"

namespace game {

void item::render() {
	// TODO
}

weapon::weapon(const itemResource* const res, unit* const host)
	: imageResource(res), host(host),
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
	// TODO
}

void weapon::onUnitCollision(unit* collider) {
	// TODO
}

void weapon::onInteractableCollision(interactable* collider) {
	// TODO
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
	: imageResource(res), health(res->maxhealth), entity(res, xpos, ypos)

{
	// TODO
}

void unit::render() {
	// TODO
}

void unit::onWeaponCollision(weapon* collider) {
	// TODO
}

void unit::onUnitCollision(unit* collider) {
	// TODO
}

void unit::onComponentCollision(component* collider) {
	// TODO
}

void unit::onInteractableCollision(interactable* collider) {
	// TODO
}

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
	// TODO
}

} // namespace game