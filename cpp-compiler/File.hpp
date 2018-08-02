#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "typedefs.hpp"
#include "loadFile.hpp"
#include "Scope.hpp"
#include "Token.hpp"
#include "Stream.hpp"
#include "StringTree.hpp"
#include "NamedValue.hpp"

static inline bool isLetterL(const u8 c) {return c >= 'a' && c <= 'z';}
static inline bool isLetterU(const u8 c) {return c >= 'A' && c <= 'Z';}
static inline bool isDigit(const u8 c) {return c >= '0' && c <= '9';}
static inline bool isOperator(const u8 c) {
	return c == '!' || c >= '#' && c <= '&' || c >= '*' && c <= '/' ||
		c >= ':' && c <= '@' || c == '^' || c == '_' || c == '|' ||
		c == '~';
}
static inline bool isGroupDelim(const u8 c) {
	return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
}

bool u8cmp(u8 *left, const char *right) {
	u32 i = 0;
	while (left[i] == right[i]) {
		if (left[i] == '\0') return true;
		++i;
	}
	return false;
}
u8 *joinU8(u8 *left, u8 *right) {
	u32 leftLen = strlen((char*)left);
	u32 rightLen = strlen((char*)right);
	u32 length = leftLen + rightLen + 1;
	u8 *result = new u8[length];
	memcpy(result, left, leftLen * sizeof(u8));
	memcpy(result + leftLen * sizeof(u8), right, rightLen * sizeof(u8));
	result[length - 1] = '\0';
	delete left;
	delete right;
	return result;
}

class File {
public:
	Scope global;
	u8 *source;
	i32 sourceLength;
	std::vector<Token> tokens;
	u32 tokenIndex = 0;
	u32 lineNumber = 0;
	u32 lineStart = 0;
	File(u8 *filename) {
		sourceLength = loadFile(filename, &source);
	}
	void printError(const char *errorType, u32 errorLoc) {
		printf("%s error! At line: %u, and character: %u. (zero indexed)\n",
			errorType, lineNumber, errorLoc - lineStart);
		wait();
		exit(1);
	}
	u32 skipLine(u32 i) { // debugging only
		while (tokens[i].id != TokenID::eol && tokens[i].id != TokenID::eof) ++i;
		return i;
	}
	#include "lex.hpp"
	#include "parse.hpp"
	void printTokens() { // debugging only
		printf("length: %lu, capacity: %lu\n\n", tokens.size(), tokens.capacity());
		for (Token& cur : tokens) {
			printf("%i, `%s`\n", cur.id, (char*)cur.getText(source));
		}
	}
};
