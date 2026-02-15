#include "main.hh"

#include "colors.h"
#include "loaderScene.hh"
#include "scene.hh"
#include "textHelper.hh"

#include <SDL3/SDL_pixels.h>
#include <exception>
#include <filesystem>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <SDL3_ttf/SDL_ttf.h>

#include "sceneManager.hh"

#include "mainMenu.hh"

#ifndef PROGRAM_NAME
#define PROGRAM_NAME ""
#endif

#define DEFAULT_WINDOW_WIDTH 1800
#define DEFAULT_WINDOW_HEIGHT 1000

using std::exception;
using std::filesystem::current_path;
using std::filesystem::path;

using common::initTextHelper;
using common::quitTextHelper;
using common::SceneManager;

using loader::buildLoaderScene;

using menu::buildMainMenu;

SDL_Window* window;
SDL_Renderer* renderer;

TTF_TextEngine* textEngine;

inline void log_error(std::exception* exp) {
	SDL_Log("%s\n", exp->what());
}

inline void log_sdl_error() {
	SDL_Log("%s\n", SDL_GetError());
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	if (argc < 1) {
		SDL_Log("Failed to find path, skipping executable location");
	} else {
		path origin(argv[0]);
		path executable(origin.parent_path());
		current_path(executable);
	}

	if (!SDL_CreateWindowAndRenderer(PROGRAM_NAME, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE,
									 &window, &renderer)) {
		log_sdl_error();
		return SDL_APP_FAILURE;
	}

	if (!SDL_SetRenderVSync(renderer, 1)) {
		log_sdl_error();
	}

	if (!TTF_Init()) {
		log_sdl_error();
		return SDL_APP_FAILURE;
	}
	textEngine = TTF_CreateRendererTextEngine(renderer);
	if (textEngine == nullptr) {
		log_sdl_error();
		return SDL_APP_FAILURE;
	}

	try {
		initTextHelper();
	} catch (exception* exp) {
		log_error(exp);
		return SDL_APP_FAILURE;
	}

	*appstate = new SceneManager(common::LOADER, buildLoaderScene);
	((SceneManager*)(*appstate))->addScene(buildMainMenu((SceneManager*)*appstate), common::MAIN_MENU);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	try {
		((SceneManager*)appstate)->getCurrentScene()->iterate();
		SDL_SetRenderDrawColor(renderer, COLOR_BLACK, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		((SceneManager*)appstate)->getCurrentScene()->render();
		SDL_RenderPresent(renderer);
		return SDL_APP_CONTINUE;
	} catch (exception* exp) {
		log_error(exp);
		return SDL_APP_FAILURE;
	}
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	if (event->type == SDL_EVENT_QUIT)
		return SDL_APP_SUCCESS;
	try {
		((SceneManager*)appstate)->getCurrentScene()->event(event);
		return SDL_APP_CONTINUE;
	} catch (exception* exp) {
		log_error(exp);
		return SDL_APP_FAILURE;
	}
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	delete (SceneManager*)appstate;
	quitTextHelper();
	TTF_Quit();
}
