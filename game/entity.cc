#include "entity.hh"
#include "itemResource.hh"

namespace game {

weapon::weapon(const itemResource* const res, unit* const host) : imageResource(res), host(host) {
	host->summons.push_back(this);
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

unit::unit(const unitResource* const res, vector<item*> items) : imageResource(res), health(res->maxhealth) {
	int vidx = 0, iidx = 0;
	if (!items.empty()) {
		primary = items[vidx++];
	} else {
		primary = nullptr;
	}
	int idx;
	for (idx = 0; idx < INVENTORY_SIZE && vidx < items.size(); idx++, vidx++) {
		inventory[idx] = items[vidx];
	}
	for (; idx < INVENTORY_SIZE; idx++) {
		inventory[idx] = nullptr;
	}
}

unit::~unit() {
	while (!summons.empty()) {
		// summons should remove themselves when deleted!
		delete summons.back();
		summons.pop_back();
	}
}

// TODO: render functions

} // namespace game