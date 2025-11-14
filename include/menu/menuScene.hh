#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>
#include <vector>

#include "element.hh"
#include "scene.hh"

using common::Scene;
using common::SceneManager;
using common::SceneType;
using std::vector;

namespace menu {

class MenuScene : public Scene {
  protected:
	vector<Element*> elements;

  public:
	MenuScene(SceneManager* context, SceneType type) : Scene(context, type) {}

	virtual void event(SDL_Event* event);

	virtual void render();

	~MenuScene();
};

} // namespace menu