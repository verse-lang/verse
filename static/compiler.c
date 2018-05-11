#include <stdio.h>
#include "loadFile.c"
#include "lexer.c"
#include "parser.c"

int main(const int argc, const char *argv[]) {
	if (argc < 2) {
		puts("You must supply a filename to compile.\n");
		return 1;
	}
	printf("argc: %i, filename: %s\n", argc, argv[1]);
	char *content;
	int size = loadFile(argv[1], &content);
	if (size < 0) {
		printf("Error loading file, %i\n", size);
		return size;
	}
	printf("%s\n", content);

	const Stream stream = {content, size, 0};
	const TokenDynArray tokens = lexer(stream);
	TokenDynArrayPrint(tokens, content);

	parser(tokens, content);
	return 0;
}
