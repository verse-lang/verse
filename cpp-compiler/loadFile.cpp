#include "loadFile.hpp"

int loadFile(const char *filename, char **result) {
	int size;
	FILE *file;
	fopen_s(&file, filename, "rb");
	if (file == nullptr) {
		*result = nullptr;
		return -1;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	*result = new char[size + 1];
	if (size != fread(*result, sizeof(char), size, file)) {
		delete *result;
		return -2;
	}
	fclose(file);
	(*result)[size] = '\0';
	return size;
}