#pragma once

#include <unordered_map>

#include <SDL3/SDL.h>

#include "scene.hh"

using std::unordered_map;

namespace common {

class SceneManager {
  private:
    Scene* current;
    unordered_map<SceneType, Scene*> scenes;

  public:
    SceneManager(Scene* menu) : current(menu) {
        scenes[MAIN_MENU] = menu;
    }

    /*
     * Adds a scene to the manager, overwriting the scene currently in that slot
     * Cannot overwrite the current scene
     */
    void addScene(Scene* scene, SceneType type);

    /*
     * Removes the scene, cannot remove the current scene
     */
    void removeScene(SceneType type);

    /*
     * Removes (exits) the current scene and loads the given scene
     */
    void exitToScene(SceneType type);

    /*
     * Loads the given scene
     */
    void focus(SceneType type);

    /*
     * gets the scene of the desired type
     */
    inline Scene* getScene(SceneType type) {
        auto itr = scenes.find(type);
        if (itr == scenes.end()) return nullptr;
        return itr->second;
    }

    /*
     * Gets the currently active scene
     */
    inline Scene* getCurrentScene() {
        return current;
    }

    /*
     * For scenes that want to use the game as a background
     * Renders the game scene, or black if it does not exist
     */
    void renderBackground(SDL_Window *window);

    ~SceneManager();
};

}  // namespace common
