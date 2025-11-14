#pragma once

#include <SDL3/SDL_render.h>

#include <SDL3_ttf/SDL_ttf.h>

// this file is for main to export information about the SDL context

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern TTF_TextEngine* textEngine;