#include "forge.hh"

#include "componentResource.hh"
#include "itemResource.hh"
#include "loader.hh"
#include "resource.hh"
#include "unitResource.hh"

#include <SDL3/SDL_render.h>

#include <stdexcept>
#include <string>

namespace loader {

inline int stoi(string& str) {
	try {
		return std::stoi(str);
	} catch (...) {
		throw new std::invalid_argument("\"" + str + "\" could not be parsed to int");
	}
}

const char* typestring(resource_type type) {
	switch (type) {
	case BACKGROUND:
		return KEYWORD_TYPE_BACKGROUND;
	case COMPONENT:
		return KEYWORD_TYPE_COMPONENT;
	case INTERACTABLE:
		return KEYWORD_TYPE_INTERACTABLE;
	case UNIT:
		return KEYWORD_TYPE_UNIT;
	case SWORD:
		return KEYWORD_TYPE_SWORD;
	case POTION:
		return KEYWORD_TYPE_POTION;
	default:
		return KEYWORD_TYPE_INVALID;
	}
}

resource::resource(unordered_map<string, node*>& attrlist) {
	auto itr = attrlist.find(KEYWORD_NAME);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_NAME);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_NAME);
	this->name = itr->second->value;
	delete itr->second;
	attrlist.erase(itr);

	itr = attrlist.find(KEYWORD_TYPE);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_TYPE);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_TYPE);

	if (!itr->second->value.compare(KEYWORD_TYPE_BACKGROUND))
		type = BACKGROUND;
	else if (!itr->second->value.compare(KEYWORD_TYPE_COMPONENT))
		type = COMPONENT;
	else if (!itr->second->value.compare(KEYWORD_TYPE_INTERACTABLE))
		type = INTERACTABLE;
	else if (!itr->second->value.compare(KEYWORD_TYPE_UNIT))
		type = UNIT;
	else if (!itr->second->value.compare(KEYWORD_TYPE_SWORD))
		type = SWORD;
	else if (!itr->second->value.compare(KEYWORD_TYPE_POTION))
		type = POTION;
	else
		throw new invalid_value_error(KEYWORD_TYPE, itr->second->value);
	delete itr->second;
	attrlist.erase(itr);

	itr = attrlist.find(KEYWORD_SIZE_X);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_SIZE_X);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_SIZE_X);
	this->size.x = stoi(itr->second->value);
	delete itr->second;
	attrlist.erase(itr);

	itr = attrlist.find(KEYWORD_SIZE_Y);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_SIZE_Y);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_SIZE_Y);
	this->size.y = stoi(itr->second->value);
	delete itr->second;
	attrlist.erase(itr);
}

itemResource::itemResource(unordered_map<string, node*>& attrlist) : resource(attrlist) {
	if (!(type & ITEM_TYPE_MASK))
		throw new invalid_value_error(KEYWORD_TYPE, string(typestring(type)));

	auto itr = attrlist.find(KEYWORD_CENTER_X);
	if (itr == attrlist.end()) {
		origin.x = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_CENTER_X);
		origin.x = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_CENTER_Y);
	if (itr == attrlist.end()) {
		origin.y = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_CENTER_Y);
		origin.y = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_STAT_DAMAGE);
	if (itr == attrlist.end()) {
		damage = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_STAT_DAMAGE);
		damage = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_STAT_SPEED);
	if (itr == attrlist.end()) {
		walkspeed = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_STAT_SPEED);
		walkspeed = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_STAT_HEALTH);
	if (itr == attrlist.end()) {
		health = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_STAT_HEALTH);
		health = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_STAT_REGEN);
	if (itr == attrlist.end()) {
		regen = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_STAT_REGEN);
		regen = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_STAT_DURATION);
	if (itr == attrlist.end()) {
		duration = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_STAT_DURATION);
		duration = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_IMAGE_PATH);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_IMAGE_PATH);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_IMAGE_PATH);
	SDL_Texture* img = imageFetch(itr->second->value);
	if (img == nullptr)
		throw new resource_not_found_error(itr->second->value);
	texture = img;
	delete itr->second;
	attrlist.erase(itr);

	if (!attrlist.empty())
		throw new unexpected_token_error(attrlist.begin()->first);
}

unitResource::unitResource(unordered_map<string, node*>& attrlist) : resource(attrlist) {
	if (!(type & UNIT_TYPE_MASK))
		throw new invalid_value_error(KEYWORD_TYPE, string(typestring(type)));

	auto itr = attrlist.find(KEYWORD_TEAM);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_TEAM);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_TEAM);
	if (!itr->second->value.compare(KEYWORD_TEAM_FRIENDLY)) {
		team = FRIENDLY;
	} else if (!itr->second->value.compare(KEYWORD_TEAM_NEUTRAL)) {
		team = NEUTRAL;
	} else if (!itr->second->value.compare(KEYWORD_TEAM_HOSTILE)) {
		team = HOSTILE;
	} else {
		throw new invalid_value_error(KEYWORD_TEAM, itr->second->value);
	}
	delete itr->second;
	attrlist.erase(itr);

	itr = attrlist.find(KEYWORD_SPEED);
	if (itr == attrlist.end()) {
		speed = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_SPEED);
		speed = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_ATTACH_X);
	if (itr == attrlist.end()) {
		attach.x = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_ATTACH_X);
		attach.x = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_ATTACH_Y);
	if (itr == attrlist.end()) {
		attach.y = 0;
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_ATTACH_Y);
		attach.y = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_HEALTH);
	if (itr == attrlist.end()) {
		throw new invalid_value_error(KEYWORD_HEALTH, itr->second->value);
	} else {
		if (itr->second->hasNext())
			throw new multiple_definitions_error(KEYWORD_HEALTH);
		maxhealth = stoi(itr->second->value);
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_ITEMS);
	if (itr != attrlist.end()) {
		node* nd = itr->second;
		while (nd) {
			const itemResource* res = itemFetch(nd->value);
			if (res == nullptr)
				throw new resource_not_found_error(nd->value);
			items.push_back(res);
		}
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_DEATH_ITEMS);
	if (itr != attrlist.end()) {
		node* nd = itr->second;
		while (nd) {
			const itemResource* res = itemFetch(nd->value);
			if (res == nullptr)
				throw new resource_not_found_error(nd->value);
			deathitems.push_back(res);
		}
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_DEATH_UNITS);
	if (itr != attrlist.end()) {
		node* nd = itr->second;
		while (nd) {
			const unitResource* res = entityFetch(nd->value);
			if (res == nullptr)
				throw new resource_not_found_error(nd->value);
			deathunits.push_back(res);
		}
		delete itr->second;
		attrlist.erase(itr);
	}

	itr = attrlist.find(KEYWORD_IMAGE_PATH);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_IMAGE_PATH);
	else {
		node* nd = itr->second;
		for (int i = 0; i < 8; i++) {
			if (nd == nullptr)
				throw new multiple_definitions_error(KEYWORD_IMAGE_PATH, i - 1, 8);
			SDL_Texture* img = imageFetch(nd->value);
			if (img == nullptr)
				throw new resource_not_found_error(nd->value);
			textures[i] = img;
			nd = nd->nxt;
		}
		if (nd)
			throw new multiple_definitions_error(KEYWORD_IMAGE_PATH, 9, 8);
		delete itr->second;
		attrlist.erase(itr);
	}

	if (!attrlist.empty())
		throw new unexpected_token_error(attrlist.begin()->first);
}

componentResource::componentResource(unordered_map<string, node*>& attrlist) : resource(attrlist) {
	if (!(type & COMPONENT_TYPE_MASK))
		throw new invalid_value_error(KEYWORD_TYPE, string(typestring(type)));

	if (type == INTERACTABLE) {
		auto itr = attrlist.find(KEYWORD_HEALTH);
		if (itr == attrlist.end()) {
			throw new invalid_value_error(KEYWORD_HEALTH, itr->second->value);
		} else {
			if (itr->second->hasNext())
				throw new multiple_definitions_error(KEYWORD_HEALTH);
			maxhealth = stoi(itr->second->value);
			delete itr->second;
			attrlist.erase(itr);
		}

		itr = attrlist.find(KEYWORD_DEATH_ITEMS);
		if (itr != attrlist.end()) {
			node* nd = itr->second;
			while (nd) {
				const itemResource* res = itemFetch(nd->value);
				if (res == nullptr)
					throw new resource_not_found_error(nd->value);
				items.push_back(res);
			}
		}
		delete itr->second;
		attrlist.erase(itr);

		itr = attrlist.find(KEYWORD_DEATH_UNITS);
		if (itr != attrlist.end()) {
			node* nd = itr->second;
			while (nd) {
				const unitResource* res = entityFetch(nd->value);
				if (res == nullptr)
					throw new resource_not_found_error(nd->value);
				units.push_back(res);
			}
		}
		delete itr->second;
		attrlist.erase(itr);
	}

	is_background = type == BACKGROUND;

	auto itr = attrlist.find(KEYWORD_IMAGE_PATH);
	if (itr == attrlist.end())
		throw new undefined_token_error(KEYWORD_IMAGE_PATH);
	if (itr->second->hasNext())
		throw new multiple_definitions_error(KEYWORD_IMAGE_PATH);
	SDL_Texture* img = imageFetch(itr->second->value);
	if (img == nullptr)
		throw new resource_not_found_error(itr->second->value);
	texture = img;
	delete itr->second;
	attrlist.erase(itr);

	if (!attrlist.empty())
		throw new unexpected_token_error(attrlist.begin()->first);
}

} // namespace loader
