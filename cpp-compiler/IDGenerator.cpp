#pragma once

#include <iostream>
#include "typedefs.cpp"

const u32 unusedID = 4294967295;
class IDGenerator {
public:
	u32 step;
	u32 maxIndex;
	u32 index;
	IDGenerator() {
		step = 2147483647;
		maxIndex = 1;
		index = 0;
	}
	u32 next() {
		if (index >= maxIndex) {
			if (step == 1) {
				printf("out of possible ids\n");
				exit(1);
			}
			step /= 2;
			maxIndex *= 2;
			index = 0;
		}
		return ((index++) * 2 + 1) * step;
	}
};