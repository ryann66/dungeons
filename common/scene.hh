#pragma once
#include <SDL3/SDL.h>

#include "sceneManager.hh"

class Scene {
  protected:
    const SceneManager context;

  public:
    Scene(SceneManager context) : context(context) { }

    /*
     * Called when a scene is becoming active
     * The scene will now begin to recieve iterate() and event() calls
     */
    virtual void onLoad();

    /*
     * Called when a scene is becoming inactive
     * The scene will no longer recieve iterate() and event() calls
     */
    virtual void onUnload();

    /*
     * Called at the tick rate of the game while this scene is active
     * Should not call render
     */
    virtual void iterate();

    /*
     * Called when an event occurs
     * Should not call render
     */
    virtual void event(SDL_Event event);

    /*
     * Called to render the scene to the given window
     * this may be called while the scene is inactive!
     */
    virtual void render(SDL_Window* window) = 0;
};