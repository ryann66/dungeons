#pragma once

#include "componentResource.hh"

namespace game {

class component {
	const int xpos, ypos, width, height;
	const componentResource* const imageResource;
};

} // namespace game