#include <limits.h>
#include <iostream>
#include "loadFile.hpp"
#include "StringTree.hpp"
#include "File.hpp"

StringTree::Tree names;
StringTree::Tree types;

i32 main(const i32 argc, const char *argv[]) {
	if (argc < 2) {
		puts("You must supply a filename to compile.\n");
		wait();
		exit(1);
	}
	printf("argc: %i, filename: %s\n\n", argc, argv[1]);
	File entry((u8*)argv[1]);
	if (entry.sourceLength < 0) {
		printf("Error loading file '%s'.\n", argv[1]);
		wait();
		exit(1);
	}
	printf("%s\n", entry.source);

	entry.lex();
	if (entry.tokens.empty()) {
		puts("empty token list");
		wait();
		exit(1);
	}
	entry.printTokens();

	entry.parse();
	wait();
	return 0;
}
