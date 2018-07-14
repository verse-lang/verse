#pragma once

#include <vector>
#include <utility>
#include "typedefs.hpp"
#include "IDGenerator.hpp"

template<typename T> class TableNode {
public:
	bool taken;
	u32 id;
	T payload;
	TableNode() {
		taken = false;
	}
};

template<typename T> class HashTable {
public:
	TableNode<T> *data;
	u32 length;
	u32 size;
	HashTable() {
		length = 0;
		size = 1;
		data = new TableNode<T>[size];
	}
	u32 hash(u32 id) {
		return id / (u32)((f32)(~((u32)0)) / (f32)size);
	}
	u32 find(u32 id) {
		u32 i = hash(id);
		u32 end = (i + size - 1) & (size - 1);
		for (; i != end; i = (i + 1) & (size - 1)) {
			if (data[i].id == id) return i;
			else if (data[i].taken == false) return unusedID;
		}
		puts("Impossibility of HashTable being full while finding.");
		exit(1);
	}
	void insert(u32 id, T item) {
		if ((f32)(size + 1) / (f32)length >= 0.7) changeSize(size * 2);
		u32 i = hash(id);
		u32 end = (i + size - 1) & (size - 1);
		for (; i != end; i = (i + 1) & (size - 1)) {
			if (data[i].taken == false) {
				data[i].taken = true;
				data[i].id = id;
				data[i].payload = item;
				return;
			}
		}
		puts("Impossibility of HashTable being full while inserting.");
		exit(1);
	}
	T read(u32 id) {
		u32 i = find(id);
		T node;
		if (i == unusedID) {
			node.id = unusedID;
		} else {
			node = data[i];
		}
		return node;
	}
	/*T remove(u32 id) { // not yet implemented.
		if ((f32)(size - 1) / (f32)length < 0.25) changeSize(size / 2);
	}*/
	void changeSize(u32 newSize) {
		TableNode<T>* oldData = data;
		u32 oldLength = length;
		u32 oldSize = size;
		data = new TableNode<T>[newSize];
		length = 0;
		size = newSize;
		for (u32 i = 0; i < oldSize; ++i) {
			if (oldData[i].taken) {
				insert(oldData[i].id, oldData[i].payload);
			}
		}
		delete oldData;
	}
};
