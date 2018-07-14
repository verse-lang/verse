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
		return 1;
	}
	printf("argc: %i, filename: %s\n", argc, argv[1]);
	File main((u8*)argv[1]);
	printf("%s\n", main.source);

	main.lex();
	if (main.tokens.empty()) {
		puts("empty token list");
		wait();
		exit(1);
	}
	main.printTokens();

	main.parse();
	wait();
	return 0;
}
