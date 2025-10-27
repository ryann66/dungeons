#include "sceneManager.hh"
#include "scene.hh"
#include <stdexcept>

void SceneManager::addScene(Scene* scene, SceneType type) {
    auto itr = scenes.find(type);
    if (itr != scenes.end()) {
        if (itr->second == current) throw new std::invalid_argument("Overwriting current scene");
        delete itr->second;
    }
}

void SceneManager::removeScene(SceneType type) {
    if (current->type == type) throw new std::invalid_argument("Erasing current scene");
    auto itr = scenes.find(type);
    if (itr == scenes.end()) throw new std::invalid_argument("Scene does not exist");
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

SceneManager::~SceneManager() {
    for (auto scn : scenes) delete scn.second;
}
