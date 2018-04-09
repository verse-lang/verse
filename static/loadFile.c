#ifndef loadFile

#include <stdio.h>

int loadFile(const char *filename, char **result) {
	int size;
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		*result = NULL;
		return -1;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	*result = (char *)malloc(size + 1);
	if (size != fread(*result, sizeof(char), size, file)) {
		free(*result);
		return -2;
	}
	fclose(file);
	(*result)[size] = '\0';
	return size;
}

#endif /* loadFile */
