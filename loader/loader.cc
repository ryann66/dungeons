#include "loader.hh"

#include <SDL3/SDL_render.h>
#include <filesystem>
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>

#include "componentResource.hh"
#include "files.h"
#include "forge.hh"
#include "itemResource.hh"
#include "main.hh"
#include "unitResource.hh"

#include <SDL3_image/SDL_image.h>

using std::ifstream;
using std::logic_error;
using std::queue;
using std::runtime_error;
using std::string;
using std::thread;
using std::unordered_map;
using std::filesystem::directory_iterator;
using std::filesystem::path;

namespace loader {

thread* loader;
runtime_error* error = nullptr;
int complete, total = 1;

unordered_map<string, componentResource*> components;
unordered_map<string, unitResource*> entities;
unordered_map<string, itemResource*> items;
unordered_map<string, SDL_Texture*> images;

inline void loadFilelistInto(const char* dirpath, queue<path>& dst) {
	directory_iterator ditr(dirpath);
	for (auto fil : ditr) {
		if (!fil.is_regular_file())
			continue;
		dst.push(fil.path());
	}
}

void launcherThread() {
	if (loader != nullptr)
		throw new logic_error("Already loading");
	if (!components.empty() || !entities.empty() || !items.empty())
		throw new logic_error("Already loaded");

	// compute todo lists
	queue<path> imglist, complist, entlist, itemlist;
	loadFilelistInto(IMAGES_FOLDER, imglist);
	loadFilelistInto(ITEMS_FOLDER, itemlist);
	loadFilelistInto(ENTITIES_FOLDER, entlist);
	loadFilelistInto(COMPONENTS_FOLDER, complist);

	// reserve map space
	images.reserve(imglist.size());
	items.reserve(itemlist.size());
	entities.reserve(entlist.size());
	components.reserve(complist.size());

	// update total
	total = imglist.size() + itemlist.size() + entlist.size() + complist.size();

	// TODO:
	// for each item on todos
	// 	create item
	//	update complete
	try {
		while (!imglist.empty()) {
			auto td = imglist.front();
			imglist.pop();

			SDL_Texture* img = IMG_LoadTexture(renderer, td.relative_path().c_str());
			if (img == nullptr)
				throw new runtime_error("Failure loading file: \"" + td.filename().string() + "\"");
			images[td.filename()] = img;
			complete++;
		}

		while (!itemlist.empty()) {
			ifstream file(itemlist.front());
			itemlist.pop();
			unordered_map<string, node*> attrs(parsefile(file));
			itemResource* res = new itemResource(attrs);
			if (!items.insert({res->name, res}).second) {
				runtime_error* err = new runtime_error("Resource name \"" + res->name + "\" reused");
				delete res;
				throw err;
			}
			complete++;
		}

		while (!entlist.empty()) {
			ifstream file(entlist.front());
			entlist.pop();
			unordered_map<string, node*> attrs(parsefile(file));
			unitResource* res = new unitResource(attrs);
			if (!entities.insert({res->name, res}).second) {
				runtime_error* err = new runtime_error("Resource name \"" + res->name + "\" reused");
				delete res;
				throw err;
			}
			complete++;
		}

		while (!complist.empty()) {
			ifstream file(complist.front());
			complist.pop();
			unordered_map<string, node*> attrs(parsefile(file));
			componentResource* res = new componentResource(attrs);
			if (!components.insert({res->name, res}).second) {
				runtime_error* err = new runtime_error("Resource name \"" + res->name + "\" reused");
				delete res;
				throw err;
			}
			complete++;
		}

		if (complete != total) {
			throw new runtime_error("File loading desync");
		}

	} catch (runtime_error* ex) {
		complete = total;
		error = ex;
	}
}

void launchLoader() {
	loader = new thread(launcherThread);
}

int percentFinish() {
	if (total != 0)
		return total / complete;
	return 0;
}

void finishLoader() {
	loader->join();
	delete loader;
	complete = 0;
	total = 1;
	delete error;
	error = nullptr;
}

void unload() {
	for (auto itr = components.begin(); itr != components.end();) {
		delete itr->second;
		itr = components.erase(itr);
	}
	for (auto itr = entities.begin(); itr != entities.end();) {
		delete itr->second;
		itr = entities.erase(itr);
	}
	for (auto itr = items.begin(); itr != items.end();) {
		delete itr->second;
		itr = items.erase(itr);
	}
	for (auto itr = images.begin(); itr != images.end();) {
		SDL_DestroyTexture(itr->second);
		itr = images.erase(itr);
	}
}

const componentResource* const componentFetch(string name) {
	return components[name];
}

const unitResource* const entityFetch(string name) {
	return entities[name];
}

const itemResource* const itemFetch(string name) {
	return items[name];
}

SDL_Texture* imageFetch(string name) {
	return images[name];
}

} // namespace loader