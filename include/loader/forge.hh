#pragma once

// COMMON ATTRIBUTES
// unique identifier to load as
#define KEYWORD_NAME "name"
// component,interactable,unit,sword,potion
#define KEYWORD_TYPE "type"
// size of bounding box
#define KEYWORD_SIZE_X "size_x"
#define KEYWORD_SIZE_Y "size_y"

// images to render
//   -items: one image
//   -units: eight images
//   -components: one image
// all images will get scaled to fit inside the bounding box
#define IMAGE_PATH "img_path"

// ITERACTABLE ATTRIBUTES (apply to everything but items and components)
// health to spawn in with
#define KEYWORD_HEALTH "max_health"
// units to spawn on death/destruction
#define KEYWORD_DEATH_UNITS "death_units"
// items to spawn on death/destruction
#define KEYWORD_DEATH_ITEMS "death_items"
// items held in inventory (also spawned on death)
#define KEYWORD_ITEMS "items"

// UNIT ATTRIBUTES
// friendly, hostile, neutral
#define KEYWORD_TEAM "team"
// unit movement speed
#define KEYWORD_SPEED "speed"
// point to attach items to
#define KEYWORD_ATTACH_X "attach_x"
#define KEYWORD_ATTACH_Y "attach_y"

// ITEM ATTRIBUTES
// point to rotate item image around
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