#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Token.hpp"
#include "StringTree.hpp"
#include "NamedValue.hpp"

// keywords: if elif while class return break continue import

bool u8cmp(u8 *left, const char *right) {
	u32 i = 0;
	while (left[i] == right[i]) {
		if (left[i] == '\0') return true;
		++i;
	}
	return false;
}

u32 skipLine(std::vector<Token> tokens, u8 *content, u32 i) { // debugging only
	while (tokens[i].id != eolID && tokens[i].id != eofID) ++i;
	while (tokens[i].id == eolID) ++i;
	return i;
}

Type readType(std::vector<Token> tokens, u8 *content, u32 i) {
	Type cur;
	return cur;
}

u32 readIf(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("if!");
	return 0;
}
u32 readElif(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("elif!");
	return 0;
}
u32 readElse(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("else!");
	return 0;
}
u32 readWhile(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("while!");
	return 0;
}
u32 readClass(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("class!");
	return 0;
}
u32 readReturn(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("return!");
	return 0;
}
u32 readBreak(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("break!");
	return 0;
}
u32 readContinue(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("continue!");
	return 0;
}
u32 readImport(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("import!");
	return 0;
}
u32 readFunction(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("function!");
	return 0;
}
u32 readTypedFunction(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("typed function!");
	return 0;
}
u32 readVariable(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("variable!");
	return 0;
}
u32 readFullExpression(std::vector<Token> tokens, u8 *content, u32 i) {
	puts("expression!");
	return 0;
}

void parser(std::vector<Token> tokens, u8 *content) {
	u16 prevIndent = 0;
	for (u32 i = 0; i < tokens.size() && tokens[i].id != eofID;) {
		Token cur = tokens[i];
		u16 indent = 0;
		if (cur.id == indentID) {
			indent = cur.end - cur.begin;
			cur = tokens[++i];
		}
		if (cur.id != eolID) {
			if ((int)indent - (int)prevIndent > 1) {
				puts("May not indent more than once!");
				wait();
				exit(1);
			}
			if (indent < prevIndent) {
				for (int diff = prevIndent - indent; diff > 0; --diff) {
					// close current scope
				}
			}
		}
		prevIndent = indent;

		u32 (*reader)(std::vector<Token>, u8*, u32) = nullptr;
		if (cur.id == identifierID) {
			u8 *text = cur.getText(content);
			u8 c = text[0];
			if (c >= 'A' && c <= 'Z') {
				//Type type = readType(tokens, content, &i);
				if (tokens[i + 1].id == identifierID) {
					Token token3 = tokens[i + 2];
					u8 *text3 = token3.getText(content);
					if (u8cmp(text3, "=>")) reader = readTypedFunction;
					else if (u8cmp(text3, "=") ||
						u8cmp(text3, ":") ||
						token3.id == eolID) reader = readVariable;
					else puts("Expected function or variable declaration.");
					delete text3;
				}
				else {
					puts("Expected an identifer after type to complete declaration.");
				}
			}
			else if (u8cmp(text, "if")) {
				reader = readIf;
			}
			else if (u8cmp(text, "elif")) {
				reader = readElif;
			}
			else if (u8cmp(text, "else")) {
				reader = readElse;
			}
			else if (u8cmp(text, "while")) {
				reader = readWhile;
			}
			else if (u8cmp(text, "class")) {
				reader = readClass;
			}
			else if (u8cmp(text, "return")) {
				reader = readReturn;
			}
			else if (u8cmp(text, "break")) {
				reader = readBreak;
			}
			else if (u8cmp(text, "continue")) {
				reader = readContinue;
			}
			else if (u8cmp(text, "import")) {
				reader = readImport;
			}
			else {
				Token second = tokens[i + 1];
				u8 *text2 = second.getText(content);
				u8 firstChar = text2[0];
				if (u8cmp(text2, "=>") ||
					(firstChar >= 'A' && firstChar <= 'Z') ||
					second.id == eolID) reader = readFunction;
				else reader = readFullExpression;
				delete text2;
			}
			delete text;
		}
		else if (cur.id == eolID) {
			++i;
			continue;
		}
		else if (cur.id == eofID) {
			//if (indent > 0) puts("Unecessary indentation before end of file.")
			return;
		} else {
			reader = readFullExpression;
		}
		if (reader != nullptr) {
			for (u32 i = 0; i < indent; ++i) printf("    ");
			reader(tokens, content, i);
			i = skipLine(tokens, content, i); // debugging
		}
		else {
			// TODO: line and u8acter numbers.
			puts("Parsing error! (at some line and some character, sorry.)");
			wait();
			exit(1);
		}
	}
}
