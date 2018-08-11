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
	File entry((u8*)argv[1], &names, &types, nullptr);
	printf("%s\n", entry.source);

	entry.lex();
	entry.printTokens();
	entry.parse();
	wait();
	return 0;
}
