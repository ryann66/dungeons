#pragma once

#include "../common/position.hh"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_surface.h>

struct element {
    position pos;

    inline SDL_Rect calcPosition(int w, int h) {

    }

    virtual void render(SDL_Surface* surf, SDL_Rect loc, bool is_hover) = 0;

    virtual bool onClick() = 0;
};
