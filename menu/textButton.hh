#pragma once

#include <string>

#include "element.hh"
#include "menuScene.hh"

using std::string;

namespace menu {

class TextButton : public Element {
    string text;
    MenuScene* context;
    bool (*callback)(MenuScene*);

  public:
    TextButton(MenuScene* context, bool (*callback)(MenuScene*), string text);

    virtual void render(SDL_Renderer* render, SDL_Rect loc, bool is_hover);

    virtual bool onClick();
};

}  // namespace menu
