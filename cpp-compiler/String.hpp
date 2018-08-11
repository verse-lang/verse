#pragma once

#include <cstring>
#include "typedefs.hpp"

class String {
public:
	u8 *content;
	u32 length;
	String(u8 *content, u32 length) : content(content), length(length) {}
	String(u8 *content) : content(content) {
		length = strlen((char*)content);
	}
	u8 &operator[](u32 index) {
		return content[index];
	}
	bool const operator==(u8 *cstr) {
		u32 i;
		for (i = 0; i < length; ++i) {
			if (content[i] != cstr[i]) {
				return false;
			}
		}
		return cstr[i] == '\0';
	}
	bool const operator!=(u8 *cstr) {
		return !(*this == cstr);
	}
};
