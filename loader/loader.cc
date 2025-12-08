#include "loader.hh"

#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>

using std::logic_error;
using std::string;
using std::thread;
using std::unordered_map;

namespace loader {

thread* loader;
int complete, total = 1;

unordered_map<string, componentResource*> components;
unordered_map<string, entityResource*> entities;
unordered_map<string, itemResource*> items;

void launcherThread() {
	if (loader != nullptr)
		throw new logic_error("Already loading");
	if (!components.empty() || !entities.empty() || !items.empty())
		throw new logic_error("Already loaded");

	// compute todo lists
	// reserve map space
	// update total

	// for each item on todo
	// 	create item
	//	update complete

	// terminate
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

const entityResource* const entityFetch(string name) {
	return entities[name];
}

const itemResource* const itemFetch(string name) {
	return items[name];
}

} // namespace loader