#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

using std::unordered_map;
using std::string;
using std::istream;

struct node {
	node(string value) : value(value), nxt(nullptr) { }
	node(string value, struct node* nxt) : value(value), nxt(nxt) { }

	~node() {
		delete nxt;
	}

	string value;
	struct node* nxt;

	inline bool hasNext() {
		return nxt != nullptr;
	}
};

/**
 * Parses a file into the key-values contained within
 */
unordered_map<string, node> parsefile(istream file);
