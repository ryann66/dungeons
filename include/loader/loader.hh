#pragma once

#include "componentResource.hh"
#include "itemResource.hh"
#include "unitResource.hh"

using game::componentResource;
using game::itemResource;
using game::unitResource;

namespace loader {

// launches a separately threaded job to load all the game resources
void launchLoader();

// gets the current percentage of finish as an int (0-100)
// note: this is subject to race conditions (not monotonic)
int percentFinish();

// joins the loader thread back into the main thread
// releases the resources held by loading, should be called after percentFinish() reaches 100
void finishLoader();

// frees all resources (don't use resource pointers after this)
void unload();

const componentResource* const componentFetch(const char* name);

const unitResource* const entityFetch(const char* name);

const itemResource* const itemFetch(const char* name);

} // namespace loader