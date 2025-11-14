#include "textButton.hh"
#include "main.hh"
#include <SDL3/SDL_render.h>

extern "C" {
#include "colors.h"
}

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

#include "textHelper.hh"

using common::renderText;

namespace menu {

TextButton::TextButton(MenuScene* context, position pos, bool (*callback)(MenuScene*), string text)
	: text(text), Element(pos), callback(callback), context(context) {}

void TextButton::render(SDL_Rect loc, bool is_hover) {
	if (!is_hover)
		SDL_SetRenderDrawColor(renderer, COLOR_BUTTON_BACKGROUND, SDL_ALPHA_OPAQUE);
	else
		SDL_SetRenderDrawColor(renderer, COLOR_BUTTON_BACKGROUND_FOCUSED, SDL_ALPHA_OPAQUE);
	SDL_FRect fr;
	SDL_RectToFRect(&loc, &fr);
	SDL_RenderRect(renderer, &fr);

	SDL_SetRenderDrawColor(renderer, COLOR_BUTTON_FOREGROUND, SDL_ALPHA_OPAQUE);
	renderText(pos, text, common::font::SMALL);
}

bool TextButton::onClick() {
	if (callback != nullptr)
		return callback(context);
	return false;
}

} // namespace menu