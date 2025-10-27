#pragma once

#include "scene.hh"
#include <unordered_map>

using std::unordered_map;

class SceneManager {
  private:
    Scene* current;
    unordered_map<SceneType, Scene*> scenes;

  public:
    SceneManager(Scene* menu) : current(menu) {
        scenes[MAIN_MENU] = menu;
    }

    void addScene(Scene* scene, SceneType type);

    void removeScene(SceneType type);

    void exitToScene(SceneType type);

    void focus(SceneType type);

    inline Scene* getScene(SceneType type) {
        auto itr = scenes.find(type);
        if (itr == scenes.end()) return nullptr;
        return itr->second;
    }

    inline Scene* getCurrentScene() {
        return current;
    }

    ~SceneManager();
};