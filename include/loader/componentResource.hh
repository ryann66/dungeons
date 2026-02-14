#pragma once

#include "itemResource.hh"
#include "parser.hh"
#include "resource.hh"
#include "unitResource.hh"

#include <vector>

#include <SDL3/SDL_render.h>

using std::vector;

namespace loader {

// component resources have only one render state
struct componentResource : public resource {
	SDL_Texture* texture;

	int maxhealth;

	// items to spawn on destruction
	vector<const itemResource*> items;

	// units to spawn on destruction
	vector<const unitResource*> units;

	/*
	 * Builds a resource from the list of attributes
	 * can throw a lot of different types of errors
	 */
	componentResource(unordered_map<string, node*>& attrlist);
};

} // namespace loader
