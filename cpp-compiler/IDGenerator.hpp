#pragma once

#include <iostream>
#include "typedefs.hpp"

const u32 unusedID = ~((u32)0);
class IDGenerator {
public:
	u32 step;
	u32 maxIndex;
	u32 index;
	IDGenerator() {
		step = unusedID / 2;
		maxIndex = 1;
		index = 0;
	}
	u32 next() {
		if (index >= maxIndex) {
			if (step == 1) {
				puts("out of possible ids");
				exit(1);
			}
			step /= 2;
			maxIndex *= 2;
			index = 0;
		}
		return ((index++) * 2 + 1) * step;
	}
};