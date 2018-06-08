#include <iostream>
#include "loadFile.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "VStream.hpp"

void printTokens(const std::vector<Token> *tokens, char *content) { // debugging only
	printf("length: %i, capacity: %i\n\n", tokens->size(), tokens->capacity());
	for (u32 n = 0; n < tokens->size(); n++) {
		const Token cur = (*tokens)[n];
		const char c = content[cur.end];
		content[cur.end] = '\0';
		printf("%i, `%s`\n", cur.id, content + cur.begin * sizeof(char));
		content[cur.end] = c;
	}
}

int main(const int argc, const char *argv[]) {
	if (argc < 2) {
		puts("You must supply a filename to compile.\n");
		system("pause");
		return 1;
	}
	printf("argc: %i, filename: %s\n", argc, argv[1]);
	char *content;
	int size = loadFile(argv[1], &content);
	if (size < 0) {
		printf("Error loading file, size: %i\n", size);
		system("pause");
		return size;
	}
	printf("%s\n", content);

	const VStream stream = { content, (u32)size, 0 };
	const std::vector<Token> tokens = lexer(stream);
	if (tokens.empty()) {
		system("pause");
		exit(1);
	}
	printTokens(&tokens, content);

	parser(tokens, content);
	system("pause");
	return 0;
}