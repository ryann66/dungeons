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

unit::~unit() {
	while (!summons.empty()) {
		// summons should remove themselves when deleted!
		delete summons[0];
	}
}

// TODO: render functions

} // namespace game