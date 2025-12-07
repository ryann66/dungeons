#pragma once

#include "componentResource.hh"
#include "effectResource.hh"
#include "entityResource.hh"
#include "itemResource.hh"

using game::componentResource;
using game::effectResource;
using game::entityResource;
using game::itemResource;

namespace loader {

// launches a separately threaded job to load all the game resources
void launchLoader();

// gets the current percentage of finish
// note: this is subject to race conditions (not monotonic)
int percentFinish();

// frees all resources (don't use resource pointers after this)
void unload();

const componentResource* const componentFetch(const char* name);

const effectResource* const effectFetch(const char* name);

const entityResource* const entityFetch(const char* name);

const itemResource* const itemFetch(const char* name);

} // namespace loader