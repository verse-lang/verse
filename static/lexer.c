#ifndef lexer

#include <stdio.h>
#include "parseTools.c"

const u8 identifierID = 0;
const u8 operatorID = 1;
const u8 indentID = 2;
const u8 eolID = 3;
const u8 numberID = 4;
const u8 stringID = 5;
const u8 groupCharID = 6;
const u8 chrID = 7;

u32 identifier(const char *text, u32 i) {
	char c = text[i];
	if (c >= 'a' && c <= 'z' ||
		c >= 'A' && c <= 'Z')
	do c = text[++i];
	while (c >= 'a' && c <= 'z' ||
		c >= 'A' && c <= 'Z' ||
		c >= '0' && c <= '9');
	return i;
}
u32 operator(const char *text, u32 i) {
	char c = text[i];
	while (c == '!' || c >= '#' && c <= '&' || c >= '*' && c <= '/' ||
		c >= ':' && c <= '@' || c == '^' || c == '_' || c == '|' ||
		c == '~') c = text[++i];
	return i;
}
u32 number(const char *text, u32 i) {
	const u32 start = i;
	char c = text[i];
	if (c >= '0' && c <= '9') {
		do c = text[++i]; while (c >= '0' && c <= '9');
		if (text[i] == '.') {
			c = text[++i];
			if (c < '0' || c > '9') {
				puts("Floats may not end with a decimal point.\n");
				return start;
			} else {
				do c = text[++i]; while (c >= '0' && c <= '9');
			}
		}
	}
	return i;
}
u32 string(const char *text, u32 i) {
	const u32 start = i;
	char c = text[i];
	if (c == '"') {
		while (true) {
			c = text[++i];
			if (c == '"') {
				return i + 1;
			} else if (c == '\\') {
				c = text[++i];
				if (c == '\0') {
					puts("Incomplete string literal. :(");
					return start;
				}
			} else if (c == '\n' || c == '\0') {
				puts("Incomplete string literal.");
				return start;
			}
		}
	}
	return i;
}
bool groupChar(const char c) {
	return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ||
		c == '}';
}
u32 comment(const char *text, u32 i) {
	char c = text[i];
	if (c == '/' && text[i + 1] == c) {
		++i;
		do c = text[++i]; while (c != '\n' && c != '\0');
	}
	return i;
}
u32 chr(const char *text, u32 i) {
	const u32 start = i;
	if (text[i] == '\'') {
		if (text[++i] == '\\') ++i;
		if (text[i]) ++i;
		else {
			puts("Missing end of character literal.");
			return start;
		}
	}
	return i;
}

TokenDynArray lexer(Stream stream) {
	const char *text = stream.content;
	u32 row = 0;
	u32 lineStart = 0;
	u32 i = stream.index;
	TokenDynArray tokens = {1, 0, (Token *)malloc(sizeof(Token))};
	while (true) {
		while (tokens.length < tokens.cap) {
			Token* current = &(tokens.data[tokens.length++]);
			current->begin = i;
			u32 end;
			if ((end = identifier(text, i)) != i) {
				current->id = identifierID;
			} else if (text[i] == ' ') { // skip
				++i;
				--tokens.length;
				continue;
			} else if ((end = operator(text, i)) != i) {
				current->id = operatorID;
			} else if (text[i] == '\t') {
				current->id = indentID;
				while (text[++i] == '\t');
				end = i;
			} else if (text[i] == '\n' || text[i] == '\r') {
				current->id = eolID;
				char c;
				do c = text[++i]; while (c == '\n' || c == 'r');
				end = i;
				lineStart = end;
				++row;
			} else if ((end = number(text, i)) != i) {
				current->id = numberID;
			} else if ((end = string(text, i)) != i) {
				current->id = stringID;
			} else if (groupChar(text[i])) {
				current->id = groupCharID;
				++i;
				end = i;
			} else if ((end = comment(text, i)) != i) { // skip
				--tokens.length;
				continue;
			} else if ((end = chr(text, i)) != i) {
				current->id = chrID;
			} else if (text[i] == '\0') {
				--tokens.length;
				return tokens;
			} else {
				printf("Lexer error, unrecognized token: Line %i, character %i.\n", row, i - lineStart);
				--tokens.length;
				TokenDynArrayPrint(tokens, (char*)text);
				tokens.length = 0;
				return tokens;
			}
			current->end = end;
			i = end;
		}
		DynArrayGrow((DynArray *)&tokens, sizeof(Token));
	}
}

#endif /* lexer */
