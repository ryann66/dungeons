#include <exception>

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>

#include "sceneManager.hh"

void log_error(std::exception* exp) {

}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    // TODO: setup main menu and return
    *appstate = new SceneManager();
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    try {
        ((SceneManager*) appstate)->getCurrentScene()->iterate();
        return SDL_APP_CONTINUE;
    } catch (std::exception* exp) {
        log_error(exp);
        return SDL_APP_FAILURE;
    }
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    try {
        ((SceneManager*) appstate)->getCurrentScene()->event(event);
        return SDL_APP_CONTINUE;
    } catch (std::exception* exp) {
        log_error(exp);
        return SDL_APP_FAILURE;
    }
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    delete (SceneManager*)appstate;
}
