#pragma once

#include <string>

#include "parser.hh"

#include <SDL3/SDL_rect.h>

// masks for converting type into resource class
#define COMPONENT_TYPE_MASK 0b11000000
#define UNIT_TYPE_MASK 0b00110000
#define ITEM_TYPE_MASK 0b00001111

using std::string;

namespace loader {

enum resource_type {
	INVALID = 0,
	COMPONENT = 0b01000000,
	INTERACTABLE = 0b10000000,
	UNIT = 0b00010000,
	SWORD = 0b00000001,
	POTION = 0b00000010
};

struct resource {
	// unique name identifier
	string name;

	// render size
	SDL_FPoint size;

	resource_type type;

	resource(unordered_map<string, node*>& attrlist);
};

} // namespace loader