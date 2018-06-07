#pragma once

#include <iostream>
#include "typedefs.cpp"

const u32 unusedID;
class IDGenerator {
public:
	u32 step;
	u32 maxIndex;
	u32 index;
	u32 next();
};