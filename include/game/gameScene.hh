#pragma once

#include "dungeon.hh"

#include "scene.hh"

namespace game {

class gameScene : public common::Scene {
  private:
	dungeon dungeon;
};

} // namespace game
