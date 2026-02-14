#pragma once

#include "componentResource.hh"
#include "itemResource.hh"
#include "unitResource.hh"

#include <stdexcept>
#include <string>

using std::string;

namespace loader {

// launches a separately threaded job to load all the game resources
void launchLoader();

// gets the current percentage of finish as an int (0-100)
// note: this is subject to race conditions (not monotonic)
int percentFinish();

// joins the loader thread back into the main thread
// releases the resources held by loading, should be called after percentFinish() reaches 100
// returns an error if loader failed
// returned error must be freed, though all other resources loaded will be freed
std::runtime_error* finishLoader();

// frees all resources (don't use resource pointers after this)
void unload();

const componentResource* const componentFetch(string name);

const unitResource* const entityFetch(string name);

const itemResource* const itemFetch(string name);

SDL_Texture* imageFetch(string name);

} // namespace loader