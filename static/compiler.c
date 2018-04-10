#include <stdio.h>
#include "loadFile.c"
#include "lexer.c"
//#include "parser.c"

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
	printf("length: %i, capacity: %i\n\n", tokens.length, tokens.cap);
	for (u32 n = 0; n < tokens.length; n++) {
		const Token cur = tokens.data[n];
		const char c = content[cur.end];
		content[cur.end] = '\0';
		printf("%i, `%s`\n", cur.id, content + cur.begin * sizeof(char));
		content[cur.end] = c;
	}
	return 0;
}
