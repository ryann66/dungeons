#include "sceneManager.hh"
#include "scene.hh"
#include "colors.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>

namespace common {

void SceneManager::addScene(Scene* scene, SceneType type) {
    auto itr = scenes.find(type);
    if (itr != scenes.end()) {
        if (itr->second == current) throw new std::invalid_argument("Overwriting current scene");
        delete itr->second;
    }
    scenes[type] = scene;
}

void SceneManager::removeScene(SceneType type) {
    if (current->type == type) throw new std::invalid_argument("Erasing current scene");
    auto itr = scenes.find(type);
    if (itr == scenes.end()) throw new std::invalid_argument("Scene does not exist");
    delete itr->second;
    scenes.erase(itr);
}

void SceneManager::exitToScene(SceneType type) {
    SceneType old = current->type;
    if (old == type) throw new std::invalid_argument("Exiting to self");
    focus(type);
    removeScene(old);
}

void SceneManager::focus(SceneType type) {
    auto itr = scenes.find(type);
    if (itr == scenes.end()) throw new std::invalid_argument("Scene does not exist");
    current->onUnload();
    current = itr->second;
    current->onLoad();
}

void SceneManager::renderBackground(SDL_Window *window) {
    auto itr = scenes[GAME];
    if (itr != nullptr) {
        itr->render(window);
        return;
    }

    // render failsafe black background
    SDL_Renderer* render = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(render, COLOR_BLACK, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    
}

SceneManager::~SceneManager() {
    for (auto scn : scenes) delete scn.second;
}

}  // namespace common
