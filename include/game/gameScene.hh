#pragma once

#include "dungeon.hh"

#include "scene.hh"

namespace game {

class gameScene : public common::Scene {
  private:
	int lastFrameTimeNS;
	int currentFrameTimeNS;

  public:
	inline int getDeltaTimeNS() const { return currentFrameTimeNS - lastFrameTimeNS; }

	inline int getCurrentFrameTimeNS() const { return currentFrameTimeNS; }

  private:
	dungeon level;
};

} // namespace game
