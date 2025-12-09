#pragma once

#include "entityResource.hh"
#include "itemResource.hh"

#include <vector>

#include <SDL3/SDL_render.h>

using std::vector;

namespace game {

// component resources have only one render state
struct componentResource {
	SDL_Texture* texture;

	int maxhealth;

	// items to spawn on destruction
	vector<itemResource*> items;

	// units to spawn on destruction
	vector<entityResource*> units;
};

} // namespace game