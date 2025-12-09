#pragma once

#include <string>
#include <vector>

#include "itemResource.hh"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

using std::string;
using std::vector;

namespace game {

// entity resources can be rendered in any of the 8 subcardinal directions, with a different image for each
struct unitResource {
	string name;

	SDL_Texture* textures[8];

	SDL_FPoint size;

	int maxhealth;
	int speed;
	int walkspeed;

	// spawn items (starting with primary hand, then inventory)
	vector<itemResource*> items;
};

} // namespace game