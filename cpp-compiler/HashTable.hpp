#pragma once

#include <vector>
#include <utility>
#include "typedefs.hpp"

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
	TableNode *data;
	u32 length;
	u32 size;
	HashTable() {
		length = 0;
		size = 1;
		data = new TableNode[size];
	}
	u32 hash(u32 id) {
		return id / (u32)((f32)(~((u32)0)) / (f32)size);
	}
	u32 find(u32 id) {
		u32 i = hash(id);

	}
	void insert(u32 id, T item) {
		if ((f32)size / (f32)(length + 1) >= 0.7) changeSize(size * 2);

	}
	T read(u32 id) {

	}
	T remove(u32 id) {
		if ((f32)size / (f32)(length - 1) < 0.25) changeSize(size / 2);

	}
	void changSize(u32 newSize) {
		TableNode* oldData = data;
		u32 oldLength = length;
		u32 oldSize = size;
		data = new TableNode[newSize];
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