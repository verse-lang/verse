#include <limits.h>
#include <iostream>
#include "loadFile.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "VStream.hpp"
#include "StringTree.hpp"

void printTokens(const std::vector<Token> *tokens, u8 *content) { // debugging only
	printf("length: %i, capacity: %i\n\n", tokens->size(), tokens->capacity());
	for (u32 n = 0; n < tokens->size(); n++) {
		Token cur = (*tokens)[n];
		printf("%i, `%s`\n", cur.id, (char*)cur.getText(content));
	}
}

StringTree::Tree stringTree;

int main(const int argc, const char *argv[]) {
	if (argc < 2) {
		puts("You must supply a filename to compile.\n");
		wait();
		return 1;
	}
	printf("argc: %i, filename: %s\n", argc, argv[1]);
	u8 *content;
	int size = loadFile(argv[1], (char**)&content);
	if (size < 0) {
		printf("Error loading file, size: %i\n", size);
		wait();
		return size;
	}
	printf("%s\n", content);

	const VStream stream = { content, (u32)size, 0 };
	const std::vector<Token> tokens = lexer(stream);
	if (tokens.empty()) {
		wait();
		exit(1);
	}
	printTokens(&tokens, content);

	parser(tokens, content);
	wait();
	return 0;
}
