#include "parser.hh"

namespace loader {

unordered_map<string, node*> parsefile(istream& file) {
	unordered_map<string, node*> rvalue;
	try {
		while (!file.eof()) {
			string line;
			file >> line;
			size_t lag = line.find_first_of(KEYWORD_SEPARATOR);
			if (lag == line.npos)
				throw new parse_error("invalid line (no separator): " + line);
			string key(line, 0, lag);
			node* nd = nullptr;

			bool loop = true;
			while (loop) {
				size_t fnt = line.find_first_of(KEYWORD_SEPARATOR, lag + 1);
				if (fnt == line.npos) {
					loop = false;
					fnt = line.length();
				}
				string value(line, lag + 1, fnt - lag - 1);
				if (value.empty()) {
					delete nd;
					throw new parse_error("Empty value for key: " + key);
				}
				nd = new node(value, nd);
				lag = fnt;
			}

			if (!rvalue.insert({key, nd}).second) {
				delete nd;
				throw new parse_error("Duplicate definitions for key: " + key);
			}
		}
		return rvalue;
	} catch (parse_error* error) {
		for (auto itr = rvalue.begin(); itr != rvalue.end();) {
			delete itr->second;
			itr = rvalue.erase(itr);
		}
		throw error;
	}
}

} // namespace loader
