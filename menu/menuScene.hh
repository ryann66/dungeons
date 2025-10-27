#pragma once

#include <vector>

#include "../common/scene.hh"
#include "element.hh"

using std::vector;

class MenuScene : public Scene {
  protected:
    vector<element> elements;

  public:
    virtual void event(SDL_Window* window, SDL_Event* event) {

    }

    virtual void render(SDL_Window* window) {

    }
};