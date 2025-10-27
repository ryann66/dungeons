#pragma once

#include "../common/position.hh"
#include <SDL3/SDL_surface.h>

struct element {
    position pos;

    virtual void render(SDL_Surface* surf, SDL_Rect loc, bool is_hover) = 0;

    virtual void onClick() = 0;
};
