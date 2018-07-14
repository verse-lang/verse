#pragma once

#include <iostream>
#include "typedefs.hpp"

i32 loadFile(u8 *filename, u8 **result) {
	i32 size;
	FILE *file = fopen((char*)filename, "rb");
	if (file == nullptr) {
		*result = nullptr;
		return -1;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	*result = (u8*)(new char[size + 1]);
	if (size != fread(*result, sizeof(char), size, file)) {
		delete *result;
		return -2;
	}
	fclose(file);
	(*result)[size] = '\0';
	return size;
}
