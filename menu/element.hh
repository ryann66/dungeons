#pragma once

#include "../common/position.hh"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_surface.h>
#include <stdexcept>

using common::position;

namespace menu {

struct element {
    position pos;

    /*
     * Calculates the bounds of this element based off the width and height of the window/surface
     */
    inline SDL_Rect calcPosition(int w, int h) {
        SDL_Rect r;
        switch (pos.anchor & ALIGN_HORIZONTAL_MASK) {
            case ALIGN_HORIZONTAL_LEFT:
                r.x = pos.xOffset;
                break;
            case ALIGN_HORIZONTAL_CENTER:
                r.x = (w - pos.xOffset - pos.width) / 2;
                break;
            case ALIGN_HORIZONTAL_RIGHT:
                r.x = w - pos.xOffset - pos.width;
                break;
            default:
                throw new std::runtime_error("invalid anchor mask (horizontal bits)");
        }
        r.w = pos.width;
        switch (pos.anchor & ALIGN_VERTICAL_MASK) {
            case ALIGN_VERTICAL_TOP:
                r.y = pos.yOffset;
                break;
            case ALIGN_VERTICAL_CENTER:
                r.y = (h - pos.yOffset - pos.height) / 2;
                break;
            case ALIGN_VERTICAL_BOTTOM:
                r.y = h - pos.yOffset - pos.height;
                break;
            default:
                throw new std::runtime_error("invalid anchor mask (vertical bits)");
        }
        r.h = pos.height;
        return r;
    }

    /*
     * Draws this element onto the surface in the given location
     */
    virtual void render(SDL_Surface* surf, SDL_Rect loc, bool is_hover) = 0;

    /*
     * Called when the element is clicked on
     * returns true iff the menu is changed (add buttons, switch scenes, etc.)
     */
    virtual bool onClick() = 0;
};

}  // namespace menu
