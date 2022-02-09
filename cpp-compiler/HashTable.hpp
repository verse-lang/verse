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
private:
	void changeCapacity(u32 newCapacity) {
		TableNode<T>* oldData = data;
		u32 oldLength = count;
		u32 oldSize = capacity;
		data = new TableNode<T>[newCapacity];
		count = 0;
		capacity = newCapacity;
		for (u32 i = 0; i < oldSize; ++i) {
			if (oldData[i].taken) {
				insert(oldData[i].id, oldData[i].payload);
			}
		}
		delete oldData;
	}
public:
	TableNode<T> *data;
	u32 count;
	u32 capacity;
	HashTable() {
		count = 0;
		capacity = 1;
		data = new TableNode<T>[capacity];
	}
	u32 hash(u32 id) {
		return id / (u32)((f32)(~((u32)0)) / (f32)capacity);
	}
	u32 find(u32 id) {
		u32 i = hash(id);
		u32 end = (i + capacity - 1) & (capacity - 1);
		for (; i != end; i = (i + 1) & (capacity - 1)) {
			if (data[i].id == id) return i;
			else if (data[i].taken == false) return unusedID;
		}
		puts("Impossibility of HashTable being full while finding.");
		exit(1);
	}
	void insert(u32 id, T item) {
		if ((f32)(++count) / (f32)(capacity + 1)  >= 0.7) {
			changeCapacity(capacity * 2);
		}
		u32 i = hash(id);
		u32 end = (i + capacity - 1) & (capacity - 1);
		for (; i != end; i = (i + 1) & (capacity - 1)) {
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
	/*T remove(u32 id) { // not yet supported or implemented.
		if ((f32)(capacity - 1) / (f32)count < 0.25) changeCapacity(capacity / 2);
	}*/
};
