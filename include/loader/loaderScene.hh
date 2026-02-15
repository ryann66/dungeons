#pragma once

#include "scene.hh"
#include "sceneManager.hh"

using common::Scene;
using common::SceneManager;
using common::SceneType;

#define LOADER_BAR_WIDTH_PERCENTAGE (0.8)
#define LOADER_BAR_HEIGHT_PERCENTAGE (0.1)
#define LOADER_BAR_X_OFFSET_PERCENTAGE (0.0)
#define LOADER_BAR_Y_OFFSET_PERCENTAGE (0.1)

namespace loader {

class LoaderScene : public Scene {
  public:
	void render();

	void onLoad();

	void iterate();

	LoaderScene(SceneManager* ctx) : Scene(ctx, common::LOADER) {}
};

Scene* buildLoaderScene(SceneManager* ctx);

} // namespace loader