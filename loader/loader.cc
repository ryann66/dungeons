#include "loader.hh"

#include <filesystem>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>

#include "files.h"

using std::logic_error;
using std::queue;
using std::string;
using std::thread;
using std::unordered_map;
using std::filesystem::directory_iterator;
using std::filesystem::path;

namespace loader {

thread* loader;
int complete, total = 1;

unordered_map<string, componentResource*> components;
unordered_map<string, unitResource*> entities;
unordered_map<string, itemResource*> items;

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
	queue<path> complist, entlist, itemlist;
	loadFilelistInto(COMPONENTS_FOLDER, complist);
	loadFilelistInto(ENTITIES_FOLDER, entlist);
	loadFilelistInto(ITEMS_FOLDER, itemlist);

	// reserve map space
	components.reserve(complist.size());
	entities.reserve(entlist.size());
	items.reserve(itemlist.size());

	// update total
	total = complist.size() + entlist.size() + itemlist.size();

	// TODO:
	// for each item on todos
	// 	create item
	//	update complete

	if (complete != total) {
		// panic?
		complete = total;
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

} // namespace loader