void lex() {
	u32 i = 0;
	Token token;
	u8 c;
	do {
		token.begin = i;
		u8 c = source[i];
		if (c == ' ') continue; // space
		else if (isLetterL(c)) { // identifier
			do c = source[++i]; while (isLetterL(c) || isDigit(c));
			token.id = TokenID::identifier;
		} else if (isOperator(c)) { // operator
			while (isOperator(source[++i]));
			token.id = TokenID::oprtr;
		} else if (c == '\t') { // indent
			while (source[++i] == '\t');
			token.id = TokenID::indent;
		} else if (isGroupDelim(c)) { // group delimiter
			++i;
			token.id = TokenID::groupDelim;
		} else if (source[i] == '\n') { // line terminator
			lineStart = i;
			++lineNumber;
			token.id = TokenID::eol;
		} else if (isDigit(c)) { // number literal
			while (isDigit(source[++i]));
			if (source[i] == '.') {
				if (isDigit(source[++i])) {
					while (isDigit(source[++i]));
				}	else {
					puts("Floating point literals may not end with a decimal point.");
					printError("Lexer");
				}
			}
			token.id = TokenID::number;
		} else if (isLetterU(c)) { // type
			do c = source[++i]; while (isLetterU(c));
			token.id = TokenID::type;
		} else if (c == '\'') { // character literal
			c = source[++i];
			if (c == '\\') i += 2;
			else if (c == '\'') {
				puts("May not have empty character literal.");
			} else ++i;
			if (source[i] == '\'') ++i;
			else {
				puts("Missing end of character literal.");
				printError("Lexer");
			}
			token.id = TokenID::character;
		} else if (c == '\0') { // end of file
			token.id = TokenID::eof;
		} else {
			puts("Unrecognized character.");
			printError("Lexer");
			tokens.clear();
		}
		token.end = i;
		tokens.push_back(token);
	} while (c != '\0');
}