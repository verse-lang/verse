#pragma once

#include <cstring>
#include "typedefs.hpp"

class String {
public:
	char *content;
	u32 length;
	String(char *_content, u32 _length) {
		content = _content;
		length = _length;
	}
	String(char *_content) {
		content = _content;
		length = strlen(_content);
	}
	char &operator[](u32 index) {
		return content[index];
	}
	bool const &operator==(char *cstr) {
		u32 i;
		for (i = 0; i < length; ++i) {
			if (content[i] != cstr[i]) {
				return false;
			}
		}
		return cstr[i] == '0';
	}
	bool const &operator!=(char *cstr) {
		return !(*this == cstr);
	}
};