#pragma once

#include "menuScene.hh"

using common::SceneManager;

namespace menu {

class MainMenuScene : public MenuScene {

  public:
    MainMenuScene(SceneManager* manager) : MenuScene(manager, SceneType::MAIN_MENU) { }
};

}  // namespace menu