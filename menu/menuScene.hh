#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>
#include <vector>

#include "../common/scene.hh"
#include "element.hh"

using std::vector;

class MenuScene : public Scene {
  protected:
    vector<element> elements;

  public:
    virtual void event(SDL_Window* window, SDL_Event* event);

    virtual void render(SDL_Window* window);
};