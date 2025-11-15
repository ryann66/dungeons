#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>

#include "main.hh"

#include "menuScene.hh"

namespace menu {

inline bool isInside(SDL_Rect bounds, float x, float y) {
	return !(bounds.x > x || bounds.x + bounds.w < x || bounds.y > y || bounds.y + bounds.h < y);
}

void MenuScene::event(SDL_Event* event) {
	if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		SDL_MouseButtonEvent* ev = (SDL_MouseButtonEvent*)event;
		if (ev->button == SDL_BUTTON_LEFT) {
			float x = ev->x, y = ev->y;
			int w, h;
			SDL_GetWindowSize(window, &w, &h);

			for (Element* el : elements) {
				if (isInside(el->calcPosition(w, h), x, y)) {
					if (el->onClick())
						return;
				}
			}
		}
	}
}

void MenuScene::render() {
	float x, y;
	SDL_GetMouseState(&x, &y);
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	for (Element* el : elements) {
		SDL_Rect pos = el->calcPosition(w, h);
		el->render(pos, isInside(pos, x, y));
	}
}

MenuScene::~MenuScene() {
	for (Element* el : elements)
		delete el;
}

} // namespace menu
