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

void printLineOfString(u8 *string, u32 startChar) {
	u32 end = startChar;
	u8 c = string[end];
	while (c != '\n' && c != '\0') c = string[++end];
	string[end] = '\0';
	printf("%s", string + sizeof(u8) * startChar);
	string[end] = c;
}

class File {
public:
	u8 *path;
	u8 *source;
	i32 sourceLength;
	std::vector<Token> tokens;
	u32 tokenIndex = 0;
	u32 lineNumber = 0;
	u32 lineStart = 0;
	Scope global;
	StringTree::Tree *names;
	StringTree::Tree *types;
	File(u8 *path, StringTree::Tree *names, StringTree::Tree *types, File *parent) :
			path(path), names(names), types(types)
	{
		sourceLength = loadFile(path, &source);
		if (sourceLength < 0) {
			printf("Could not read file '%s', does it exist?\n", path);
			if (parent != nullptr) {
				printf("In file %s, line %u:\n ", parent->path,
					parent->lineNumber);
				printLineOfString(parent->source, parent->lineStart);
				printf("\n");
			}
			printError("Reading file");
		}
	}
	void printError(const char *errorType) {
		printf("%s error!\n", errorType);
		wait();
		exit(1);
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
	void lex();
	u32 readType(Token);
	void parse();
	void printTokens() { // debugging only
		printf("length: %lu, capacity: %lu\n\n", tokens.size(), tokens.capacity());
		for (Token& cur : tokens) {
			printf("%i, `%s`\n", cur.id, (char*)cur.getText(source));
		}
	}
};

#include "lex.hpp"
#include "parse.hpp"
