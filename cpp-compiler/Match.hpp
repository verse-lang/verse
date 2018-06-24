#pragma once

#include "typedefs.hpp"

class Match {
public:
	u32 begin;
	u32 end;
	u8 *getText(u8 *source) {
		u32 length = end - begin;
		//printf("len: %u\n", length);
		//if (length < 0) {
		//	puts("UH OH!");
		//	length = 0;
		//}
		u8 *temp = new u8[length + 1]; // + 1 for null char
		temp[length] = '\0';
		// Having issues with IDE recognizing <cstring>, I would prefer to use memcpy().
		for (u32 i = begin; i < end; ++i) temp[i - begin] = source[i];
		return temp;
	}
};