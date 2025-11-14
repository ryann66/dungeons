#include "main.hh"

#include <exception>

#define SDL_MAIN_USE_CALLBACKS
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

using common::Scene;
using common::SceneManager;

using menu::buildMainMenu;

SDL_Window* window;
SDL_Renderer* renderer;

TTF_TextEngine* textEngine;

void log_error(std::exception* exp) { SDL_Log("%s\n", exp->what()); }

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	// TODO: setup main menu and return
	*appstate = new SceneManager(buildMainMenu);
	SDL_CreateWindowAndRenderer(PROGRAM_NAME, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0, &window, &renderer);

	TTF_Init();
	textEngine = TTF_CreateRendererTextEngine(renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	try {
		Scene* scn = ((SceneManager*)appstate)->getCurrentScene();
		scn->iterate();
		scn->render();
		return SDL_APP_CONTINUE;
	} catch (std::exception* exp) {
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
	} catch (std::exception* exp) {
		log_error(exp);
		return SDL_APP_FAILURE;
	}
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) { delete (SceneManager*)appstate; }
