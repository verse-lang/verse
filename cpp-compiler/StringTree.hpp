#pragma once

#include <vector>
#include <utility>
#include "IDGenerator.hpp"
#include "typedefs.hpp"
#include "String.hpp"

class StringTreeNode {
public:
	std::vector<std::pair<char*, u32>> strings;
	StringTreeNode *next[256];
	StringTreeNode() {
		for (u8 i = 0; i < 256; ++i) strings[i].second = unusedID;
		for (u8 i = 0; i < 256; ++i) next[i] = nullptr;
	}
};

class StringTree {
public:
	IDGenerator *idGenerator;
	StringTreeNode root;
	StringTree(IDGenerator *_idGenerator) {
		idGenerator = _idGenerator;
	}
	u32 label(String string) {
		StringTreeNode *cur = &root;
		for (u32 i = 0; i < string.length - 1; ++i) {
			if (cur->next[string[i]] == nullptr) {
				cur->next[string[i]] = new StringTreeNode();
			}
			cur = cur->next[string[i]];
		}
		std::vector<std::pair<char*, u32>> strs = cur->strings;
		for (auto pair : strs) {
			if (string == pair.first) {
				return pair.second;
			}
		}
		u32 id = idGenerator->next();
		strs.push_back(std::pair<char*, u32>(string.content, id));
		return id;
	}
};