#ifndef parser

#include <stdio.h>
#include "parseTools.c"

void parser(TokenDynArray tokenArr, char* text) {
	u32 n = 0;
	const Token* tokens = tokenArr.data;
	Token cur;
	while (true) {
		cur = tokens[n];
		if (MatchEqualsString(cur, ))
	}
}
#endif // parser
