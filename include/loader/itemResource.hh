#pragma once

#include <string>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

using std::string;

namespace game {

// item resources can be rendered in any orientation, but only one image is used (rotated)
struct itemResource {
	string name;

	SDL_Texture* texture;

	// size (for rendering, hitbox, etc)
	SDL_FPoint size;

	// point to rotate around (not constrained to weapon bounds)
	SDL_FPoint origin;

	enum { SWORD, POTION } category;

	union {
		struct {
			int damage;
			int speed;
		} sword;

		struct {
			// health change (instant)
			int health;

			// health change per second
			int heal;

			// speed stat change (removed on duration)
			int speed;

			// walkspeed stat change (removed on duration)
			int walkspeed;

			// duration in seconds (0 for instant)
			int duration;
		} potion;
	} data;
};

} // namespace game