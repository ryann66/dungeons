#include "mainMenu.hh"

namespace menu {

MainMenuScene::MainMenuScene(SceneManager* manager) : MenuScene(manager, SceneType::MAIN_MENU) {
    // TODO
}

Scene* buildMainMenu(SceneManager* ctx) {
    return new MainMenuScene(ctx);
}

}  // namespace menu