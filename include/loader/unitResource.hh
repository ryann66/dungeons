#pragma once

#include <string>
#include <vector>

#include "itemResource.hh"
#include "parser.hh"
#include "resource.hh"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

using std::string;
using std::vector;

namespace loader {

enum unit_team { FRIENDLY = 1, NEUTRAL = 0, HOSTILE = 2 };

#define UNITS_HOSTILE(t1, t2) ((t1) | (t2) == 3)
#define UNITS_FRIENDLY(t1, t2) (!(UNITS_HOSTILE(t1, t2)))

// entity resources can be rendered in any of the 8 subcardinal directions, with a different image for each
struct unitResource : public resource {
	SDL_Texture* textures[8];

	SDL_FPoint attach;

	int maxhealth;
	int speed;
	int walkspeed;
	int strength;

	unit_team team;

	// spawn items (starting with primary hand, then inventory)
	vector<const itemResource*> items;

	// items to spawn on death
	vector<const itemResource*> deathitems;

	// units to spawn on death
	vector<const unitResource*> deathunits;

	/*
	 * Builds a resource from the list of attributes
	 * can throw a lot of different types of errors
	 */
	unitResource(unordered_map<string, node*>& attrlist);
};

} // namespace loader
