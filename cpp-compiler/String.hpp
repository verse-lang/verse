#pragma once

#include "typedefs.hpp"

class String {
public:
	char *content;
	u32 length;
	String(char *_content, u32 _length) {
		content = _content;
		length = _length;
	}
};