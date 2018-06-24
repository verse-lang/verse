#pragma once

#include <vector>
#include "IDGenerator.hpp"
#include "typedefs.hpp"
#include "String.hpp"

namespace StringTree {
	class Packet {
	public:
		u8* string;
		u32 id;
		Packet() {
			id = unusedID;
		}
		Packet(u8 *str, u32 label) {
			string = str;
			id = label;
		}
	};
	class Node {
	public:
		std::vector<Packet> packets;
		Node *next[256];
		Node() {
			memset(next, 0, 256 * sizeof(Node*));
		}
	};
	class Tree {
	public:
		IDGenerator idGenerator;
		StringTree::Node root;
		u32 label(String string) {
			StringTree::Node *cur = &root;
			for (u32 i = 0; i < string.length - 1; ++i) {
				if (cur->next[string[i]] == nullptr) {
					cur->next[string[i]] = new StringTree::Node();
				}
				cur = cur->next[string[i]];
			}
			for (auto packet : cur->packets) {
				if (string == packet.string) {
					return packet.id;
				}
			}
			u32 id = idGenerator.next();
			cur->packets.push_back(Packet(string.content, id));
			return id;
		}
	};
}