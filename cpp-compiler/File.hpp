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
#include "Expression.hpp"

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
	void printErrorLoc(u32 errorLoc) {
		printf("%s%s:%u:%u%s\n", "\033[1;97;40m", path,
			lineNumber + 1, errorLoc - lineStart, "\033[0m");
		u32 lineBegin = lineStart;
		while (source[lineBegin] == '\t') ++lineBegin;
		u32 lineEnd = errorLoc;
		while (source[lineEnd] != '\n' && source[lineEnd] != '\0') {
			++lineEnd;
		}
		u8* beforeError = Match{lineBegin, errorLoc}.getText(source);
		u8* afterError = Match{errorLoc, lineEnd}.getText(source);
		printf("\033[0;32;40m%s\033[0m", beforeError);
		printf("%s%s%s\n", "\033[0;31;40m", afterError, "\033[0m");
		delete beforeError;
		delete afterError;
		wait();
		exit(1);
	}
	u32 skipLine(u32 i) { // debugging only
		while (tokens[i].id != TokenID::eol && tokens[i].id != TokenID::eof) ++i;
		return i;
	}
	void lex();
	u32 readType(Token);
	Expression *parseExpression();
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
