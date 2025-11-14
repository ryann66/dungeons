#pragma once

#include <string>

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "position.hh"

using std::string;

namespace common {

// clang-format off
enum font {
	TINY, SMALL, MEDIUM, LARGE, EXTRA_LARGE,
	TITLE_MEDIUM,	TITLE_LARGE, TITLE_EXTRA_LARGE,
	INVALID // INVALID must be the last font in the enum
};
// clang-format on

/*
 * Draws the string inside the given bounding box
 * Excess space will be given to alignment as specified
 */
void renderText(const position& pos, string& str, font font);

/*
 * Initializes the text helper library
 */
void initTextHelper();

/*
 * Frees resources used by the text helper library
 */
void quitTextHelper();

} // namespace common
