#pragma once
#include <SDL3/SDL.h>

namespace common {

class SceneManager;

enum SceneType { LOADER, MAIN_MENU, SETTINGS, GAME };

class Scene {
  protected:
	SceneManager* context;

  public:
	const SceneType type;

	Scene(SceneManager* context, SceneType type) : context(context), type(type) {}

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
	virtual void event(SDL_Event* event);

	/*
	 * Called to render the scene to the window
	 * this may be called while the scene is inactive!
	 */
	virtual void render() = 0;

	virtual ~Scene() = default;
};

} // namespace common
