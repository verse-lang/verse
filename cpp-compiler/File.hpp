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
	File(u8 *filename) {
		int size;
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
	void printTokens() { // debugging only
		printf("length: %lu, capacity: %lu\n\n", tokens.size(), tokens.capacity());
		for (u32 n = 0; n < tokens.size(); n++) {
			Token cur = tokens[n];
			printf("%i, `%s`\n", cur.id, (char*)cur.getText(source));
		}
	}
};
