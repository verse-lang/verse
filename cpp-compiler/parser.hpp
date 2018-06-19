#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Token.hpp"
#include "StringTree.hpp"
#include "NamedValue.hpp"

u32 skipLine(std::vector<Token> tokens, char *content, u32 i) { // debugging only
	while (tokens[i].id != eolID && tokens[i].id != eofID) ++i;
	while (tokens[i].id == eolID) ++i;
	return i;
}

Type readType(std::vector<Token> tokens, char *content, u32 i) {
	Type cur;
	return cur;
}

u32 readIf(std::vector<Token> tokens, char *content, u32 i) {
	puts("if!");
	return 0;
}
u32 readElif(std::vector<Token> tokens, char *content, u32 i) {
	puts("elif!");
	return 0;
}
u32 readWhile(std::vector<Token> tokens, char *content, u32 i) {
	puts("while!");
	return 0;
}
u32 readClass(std::vector<Token> tokens, char *content, u32 i) {
	puts("class!");
	return 0;
}
u32 readImport(std::vector<Token> tokens, char *content, u32 i) {
	puts("import!");
	return 0;
}
u32 readFunction(std::vector<Token> tokens, char *content, u32 i) {
	puts("function!");
	return 0;
}
u32 readTypedFunction(std::vector<Token> tokens, char *content, u32 i) {
	puts("typed function!");
	return 0;
}
u32 readVariable(std::vector<Token> tokens, char *content, u32 i) {
	puts("variable!");
	return 0;
}
u32 readFullExpression(std::vector<Token> tokens, char *content, u32 i) {
	puts("expression!");
	return 0;
}

void parser(std::vector<Token> tokens, char *content) {
	u16 prevIndent = 0;
	for (u32 i = 0; i < tokens.size() && tokens[i].id != eofID;) {
		u16 indent = 0;
		while (tokens[i].id == indentID) {
			++i;
			++indent;
		}
		Token cur = tokens[i];
		if (cur.id != eolID) {
			for (int diff = prevIndent - indent; diff > 0; --diff) {
				puts("closing scope");
			}
		}
		prevIndent = indent;

		u32 (*reader)(std::vector<Token>, char*, u32) = nullptr;
		if (cur.id == identifierID) {
			std::string text = std::string(cur.getText(content));
			char c = text[0];
			if (c >= 'A' && c <= 'Z') {
				//Type type = readType(tokens, content, i);
				if (tokens[i + 1].id == identifierID) {
					Token token3 = tokens[i + 2];
					std::string text3 = std::string(token3.getText(content));
					if (text3 == "=>") reader = readTypedFunction;
					else if (text3 == "=" || token3.id == eolID) reader = readVariable;
					else puts("Expected function or variable declaration.");
				}
				else {
					puts("Expected an identifer after type to complete declaration.");
				}
			}
			else if (text == "if") {
				reader = readIf;
			}
			else if (text == "elif") {
				reader = readElif;
			}
			else if (text == "while") {
				reader = readWhile;
			}
			else if (text == "class") {
				reader = readClass;
			}
			else if (text == "import") {
				reader = readImport;
			}
			else {
				Token second = tokens[i + 1];
				std::string text2 = std::string(second.getText(content));
				if (text2 == "=>") reader = readFunction;
				else reader = readFullExpression;
			}
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
			reader(tokens, content, i);
			i = skipLine(tokens, content, i); // debugging
		}
		else {
			// TODO: line and character numbers.
			puts("Parsing error! (at some line and some character, sorry.)");
			system("pause");
			exit(1);
		}
	}
}