#pragma once

#include <stdexcept>
#include <string>

using std::string;
using std::to_string;

// COMMON ATTRIBUTES
// unique identifier to load as
#define KEYWORD_NAME "name"
// component,interactable,unit,sword,potion
#define KEYWORD_TYPE "type"
// size of bounding box
#define KEYWORD_SIZE_X "size_x"
#define KEYWORD_SIZE_Y "size_y"

// TYPES
#define KEYWORD_TYPE_INVALID "invalid"
#define KEYWORD_TYPE_COMPONENT "component"
#define KEYWORD_TYPE_INTERACTABLE "interactable"
#define KEYWORD_TYPE_UNIT "unit"
#define KEYWORD_TYPE_SWORD "sword"
#define KEYWORD_TYPE_POTION "potion"

// images to render
//   -items: one image
//   -units: eight images (in order N, NE, E, etc..)
//   -components: one image
// all images will get scaled to fit inside the bounding box
#define KEYWORD_IMAGE_PATH "img_path"

// ITERACTABLE ATTRIBUTES (apply to everything but items and components)
// health to spawn in with
#define KEYWORD_HEALTH "max_health"
// units to spawn on death/destruction
#define KEYWORD_DEATH_UNITS "death_units"
// items to spawn on death/destruction
#define KEYWORD_DEATH_ITEMS "death_items"

// UNIT ATTRIBUTES
// team (see TEAMS below)
#define KEYWORD_TEAM "team"
// unit movement speed
#define KEYWORD_SPEED "speed"
// items held in inventory (also spawned on death)
#define KEYWORD_ITEMS "items"
// point to attach items to
#define KEYWORD_ATTACH_X "attach_x"
#define KEYWORD_ATTACH_Y "attach_y"

// TEAMS
#define KEYWORD_TEAM_FRIENDLY "friendly"
#define KEYWORD_TEAM_NEUTRAL "neutral"
#define KEYWORD_TEAM_HOSTILE "hostile"

// ITEM ATTRIBUTES
// point to rotate item image around (also the point that is attached to units)
#define KEYWORD_CENTER_X "center_x"
#define KEYWORD_CENTER_Y "center_y"
// damage increase
#define KEYWORD_STAT_DAMAGE "attr_damage"
// speed increase
#define KEYWORD_STAT_SPEED "attr_speed"
// health increase
#define KEYWORD_STAT_HEALTH "attr_health"
// health regen
#define KEYWORD_STAT_REGEN "attr_regen"
// length of effect (only for consumables)
#define KEYWORD_STAT_DURATION "attr_duration"

namespace loader {

class unexpected_token_error : public std::runtime_error {
  public:
	unexpected_token_error(string keyword) : std::runtime_error("Keyword \"" + keyword + "\" was not expected here") {}
};

class undefined_token_error : public std::runtime_error {
  public:
	undefined_token_error(string keyword) : std::runtime_error("Keyword \"" + keyword + "\" must be defined") {}
};

class multiple_definitions_error : public std::runtime_error {
  public:
	multiple_definitions_error(string keyword)
		: std::runtime_error("Keyword \"" + keyword + "\" was defined more than once") {}

	multiple_definitions_error(string keyword, int count, int target)
		: std::runtime_error("Keyword \"" + keyword + "\" was defined " + to_string(count) + " times instead of " +
							 to_string(target) + " times") {}
};

class invalid_value_error : public std::runtime_error {
  public:
	invalid_value_error(string keyword, string value)
		: std::runtime_error("\"" + value + "\" is not a valid value for key \"" + keyword + "\"") {}
};

class resource_not_found_error : public std::runtime_error {
  public:
	resource_not_found_error(string item) : std::runtime_error("Resource \"" + item + "\" not found") {}
};

} // namespace loader
