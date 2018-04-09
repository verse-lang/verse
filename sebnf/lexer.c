#include <stdio.h>
#include <stdint.h>
#include "test.c"

int main(int argc, char *argv)
{
	hello();
	char *content;
	int size = loadFile("parser.sebnf", &content);
	if (size < 0) {
		puts("Error loading file");
		return size;
	}
	printf("%s\n", content);
	printf("%i\n", sizeof(Match));

	return 0;
}

int loadFile(const char *filename, char **result) {
	int size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		*result = NULL;
		return -1;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*result = (char *)malloc(size+1);
	if (size != fread(*result, sizeof(char), size, f)) {
		free(*result);
		return -2;
	}
	fclose(f);
	(*result)[size] = 0;
	return size;
}
