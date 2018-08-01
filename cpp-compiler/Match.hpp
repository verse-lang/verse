#pragma once

#include <cstring>
#include "typedefs.hpp"

class Match {
public:
	u32 begin;
	u32 end;
	u8 *getText(u8 *source) {
		u32 length = end - begin;
		u8 *temp = new u8[length + 1]; // + 1 for null char
		temp[length] = '\0';
		memcpy(temp, source + begin * sizeof(u8), (end - begin) * sizeof(u8));
		return temp;
	}
};
