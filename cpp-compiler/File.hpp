#pragma once

#include "typedefs.hpp"
#include "loadFile.hpp"
#include "Scope.hpp"
#include "lexer.hpp"
#include "parser.hpp"

class File {
public:
	Scope global;
	u8 *source;
	std::vector<Token> tokens;
	File(u8 *filename) {
		i32 size;
		size = loadFile(filename, &source);
		if (size < 0) {
			printf("Error loading file, size: %i\n", size);
			wait();
			exit(1);
		}
	}
	void lex() {
		tokens = lexer(source);
	}
	void parse() {
		parser(tokens, source);
	}
	void printTokens() { // debugging only
		printf("length: %lu, capacity: %lu\n\n", tokens.size(), tokens.capacity());
		for (Token& cur : tokens) {
			printf("%i, `%s`\n", cur.id, (char*)cur.getText(source));
		}
	}
};
