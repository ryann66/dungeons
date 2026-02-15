#include "loaderScene.hh"

#include "colors.h"
#include "error_codes.h"
#include "loader.hh"
#include "main.hh"
#include "scene.hh"
#include "sceneManager.hh"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>

using std::runtime_error;

namespace loader {

void LoaderScene::onLoad() {
	launchLoader();
}

void LoaderScene::render() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	SDL_SetRenderDrawColor(renderer, COLOR_LOADER_UNFILLED, SDL_ALPHA_OPAQUE);
	SDL_FRect bar;
	bar.h = ((float)h) * LOADER_BAR_HEIGHT_PERCENTAGE;
	bar.w = ((float)w) * LOADER_BAR_WIDTH_PERCENTAGE;
	bar.y = ((float)h) / 2 - bar.h / 2 + ((float)h) * LOADER_BAR_Y_OFFSET_PERCENTAGE;
	bar.x = ((float)w) / 2 - bar.w / 2 + ((float)w) * LOADER_BAR_X_OFFSET_PERCENTAGE;
	SDL_RenderFillRect(renderer, &bar);

	SDL_SetRenderDrawColor(renderer, COLOR_LOADER_FILLED, SDL_ALPHA_OPAQUE);
	bar.w *= percentFinish();
	bar.w /= 100;
	SDL_RenderFillRect(renderer, &bar);
}

void LoaderScene::iterate() {
	if (percentFinish() == 100) {
		runtime_error* err = finishLoader();
		if (err) {
			SDL_Log("%s\n", err->what());
			delete err;
			exit(ERROR_LOADER_FAILURE);
		}
		context->exitToScene(common::MAIN_MENU);
	}
}

Scene* buildLoaderScene(SceneManager* ctx) {
	return new LoaderScene(ctx);
}

} // namespace loader