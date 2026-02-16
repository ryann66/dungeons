#pragma once

#include <string>

#include "parser.hh"
#include "resource.hh"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

using std::string;

namespace loader {

// item resources can be rendered in any orientation, but only one image is used (rotated)
struct itemResource : public resource {
	SDL_Texture* texture;

	// point to rotate around (not constrained to item bounds)
	SDL_FPoint origin;

	// damage
	int damage;

	// health change
	int health;

	// health change per second
	int regen;

	// walkspeed stat change
	int walkspeed;

	// duration in seconds (0 for instant)
	int duration;

	/*
	 * Builds a resource from the list of attributes
	 * can throw a lot of different types of errors
	 */
	itemResource(unordered_map<string, node*>& attrlist);
};

} // namespace loader
