#include "textButton.hh"

extern "C" {
    #include "colors.h"
}

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

namespace menu {

TextButton::TextButton(MenuScene* context, bool (*callback)(MenuScene*), string text) : text(text), callback(callback), context(context) { }

void TextButton::render(SDL_Renderer* render, SDL_Rect loc, bool is_hover) {
    if (!is_hover) SDL_SetRenderDrawColor(render, COLOR_BUTTON_BACKGROUND, SDL_ALPHA_OPAQUE);
    else SDL_SetRenderDrawColor(render, COLOR_BUTTON_BACKGROUND_FOCUSED, SDL_ALPHA_OPAQUE);
    SDL_FRect fr;
    SDL_RectToFRect(&loc, &fr);
    SDL_RenderRect(render, &fr);
}

bool TextButton::onClick() {
    if (callback != nullptr) return callback(context);
    return false;
}

}  // namespace menu