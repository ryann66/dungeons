#include "mainMenu.hh"
#include "position.hh"
#include "textButton.hh"

using common::Anchor;

namespace menu {

MainMenuScene::MainMenuScene(SceneManager* manager) : MenuScene(manager, SceneType::MAIN_MENU) {
	elements.push_back(new TextButton(
		this, (position){.anchor = Anchor::CENTER, .xOffset = 0, .yOffset = 0, .width = 100, .height = 50}, nullptr,
		"Foo"));
}

Scene* buildMainMenu(SceneManager* ctx) { return new MainMenuScene(ctx); }

} // namespace menu