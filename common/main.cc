#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <exception>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>

#include "sceneManager.hh"

using common::SceneManager;
using common::Scene;

void log_error(std::exception* exp) {

}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    // TODO: setup main menu and return
    *appstate = new SceneManager();
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    try {
        Scene* scn = ((SceneManager*) appstate)->getCurrentScene();
        scn->iterate();
        scn->render(SDL_GL_GetCurrentWindow());
        return SDL_APP_CONTINUE;
    } catch (std::exception* exp) {
        log_error(exp);
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    try {
        ((SceneManager*) appstate)->getCurrentScene()->event(SDL_GL_GetCurrentWindow(), event);
        return SDL_APP_CONTINUE;
    } catch (std::exception* exp) {
        log_error(exp);
        return SDL_APP_FAILURE;
    }
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    delete (SceneManager*)appstate;
}
