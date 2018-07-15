#pragma once

#include "typedefs.hpp"
#include "loadFile.hpp"
#include "Scope.hpp"
#include "lexer.hpp"

class File {
public:
	Scope global;
	u8 *source;
	std::vector<Token> tokens;
	File(u8 *filename);
	void lex();
	void parse();
	void printTokens();
};

#include "parser.hpp"

File::File(u8 *filename) {
	i32 size;
	size = loadFile(filename, &source);
	if (size < 0) {
		printf("Error loading file, size: %i\n", size);
		wait();
		exit(1);
	}
}
void File::lex() {
	tokens = lexer(source);
}
void File::parse() {
	parser(this);
}
void File::printTokens() { // debugging only
	printf("length: %lu, capacity: %lu\n\n", tokens.size(), tokens.capacity());
	for (Token& cur : tokens) {
		printf("%i, `%s`\n", cur.id, (char*)cur.getText(source));
	}
}
