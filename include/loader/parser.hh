#pragma once

// character used to separate keywords
#define KEYWORD_SEPARATOR ':'

#include <string>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

using std::unordered_map;
using std::string;
using std::istream;

class parse_error : public std::runtime_error { 
	public:
	parse_error(string msg) : std::runtime_error(msg) {}
};

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
 * Nodes in collection must be freed
 */
unordered_map<string, node*> parsefile(istream file);
