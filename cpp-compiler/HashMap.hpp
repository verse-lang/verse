#pragma once

#include <vector>
#include <utility>
#include "typedefs.cpp"

template<typename T> class HashMap {
public:
	std::vector<std::pair<u32, T>> data;
	T get(u32 id);
	void set(u32 id, T item);
};