#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include "sceneManager.hh"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    *appstate = new SceneManager();
}

SDL_AppResult SDL_AppIterate(void* appstate) {

}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {

}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    delete (SceneManager*)appstate;
}
