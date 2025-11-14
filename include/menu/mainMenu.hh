#pragma once

#include "menuScene.hh"
#include "scene.hh"
#include "sceneManager.hh"

using common::SceneManager;

namespace menu {

class MainMenuScene : public MenuScene {
  public:
	MainMenuScene(SceneManager* manager);
};

Scene* buildMainMenu(SceneManager* ctx);

}  // namespace menu