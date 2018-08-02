u32 readType() {

	return 0;
}

void parse() {
	lineNumber = 0;
	u16 prevIndent = 0;
	Token cur;
	for (u32 i = 0; i < tokens.size() && tokens[i].id != TokenID::eof;) {
		u16 indent = 0;
		for (;true;++i) {
			cur = tokens[i];
			if (cur.id == TokenID::eol) ++lineNumber;
			else if (cur.id == TokenID::indent) indent = cur.end - cur.begin;
			else break;
		}
		i32 indentDiff = (i32)indent - (i32)prevIndent;
		if (indentDiff > 1) {
			puts("May not indent more than once!");
			printError("Parser", cur.begin);
		} else if (indentDiff < 0) {
			for (i32 n = indentDiff; n > 0; --n) {
				// close current scope
			}
		}
		prevIndent = indent;
		lineStart = cur.begin - indent;

		if (cur.id == TokenID::identifier) {
			u8 *text = cur.getText(source);
			if (u8cmp(text, "if")) {
				puts("if!");
			} else if (u8cmp(text, "elif")) {
				puts("elif!");
			} else if (u8cmp(text, "else")) {
				puts("else!");
			} else if (u8cmp(text, "while")) {
				puts("while!");
			} else if (u8cmp(text, "class")) {
				puts("class!");
			} else if (u8cmp(text, "return")) {
				puts("return!");
			} else if (u8cmp(text, "break")) {
				puts("break!");
			} else if (u8cmp(text, "continue")) {
				puts("continue!");
			} else if (u8cmp(text, "import")) {
				puts("import!");
				Token second = tokens[i + 1];
				Token third = tokens[i + 2];
				u8 *thirdText = third.getText(source);
				if (false) {

				} else if (second.id == TokenID::identifier && u8cmp(thirdText, "from")) {
					u8 *path = new u8[1];
					path[0] = '\0';
					for (u32 n = tokenIndex + 3; true; ++n) {
						Token next = tokens[n];
						if (next.id == TokenID::eol || next.id == TokenID::eof) {
							path = joinU8(path, next.getText(source));
						} else break;
					}
					File temp(path);
				} else if (false) {

				} else {
					puts("Unrecognized import format.");
					delete thirdText;
					printError("Parser", cur.begin);
				}
				delete thirdText;
			} else {
				Token second = tokens[i + 1];
				u8 *text2 = second.getText(source);
				u8 firstChar = text2[0];
				if ((firstChar >= 'A' && firstChar <= 'Z') || u8cmp(text2, "=>") || second.id == TokenID::eol) {
					puts("function!");
				} else {
					puts("expression!");
				}
				delete text2;
			}
			delete text;
		} else if (cur.id == TokenID::type) {
			u32 typeID = readType();
			if (tokens[i + 1].id == TokenID::identifier) {
				Token token3 = tokens[i + 2];
				u8 *text3 = token3.getText(source);
				if (u8cmp(text3, "=")) {
					puts("initialized variable!");
				} else if (u8cmp(text3, ":")) {
					puts("class member!");
				} else if (token3.id == TokenID::eol) {
					puts("uninitialized variable!");
				} else puts("Expected variable declaration.");
				delete text3;
			} else {
				puts("Expected an identifer after type to complete declaration.");
				printError("Parser", cur.begin);
			}
		} else {
			puts("expression!");
		}
		i = skipLine(i);
	}
}
