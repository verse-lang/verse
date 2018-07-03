# The Verse Programming Language

Statically typed, concise syntax, classes, templates, const correctness, semi-functional style.

Why am I making my own language?
	C doesn't have classes or templates, C++ is too complicated, JavaScript doesn't have static typing, etc.
	Yes there are other languages I could use, but in general they have 'syntax fluff' like semicolons and curly brackets surrounding blocks.
	Yes there are languages that don't have those things; in the end I want to make my own language for the learning experience.

The original plan was to compile to C, because that would be the easiest solution, however I decided compiling to LLVM IR and feeding it through the optimizer would give the best results.

Currently the project is in the pre-alpha development stage; nothing can actually be compiled.
As soon as I can compile Verse code into an executable that can compile itself, (a self-hosting compiler), I'll move the project into the alpha stage, and start work on documentation and tutorials for people to write their own Verse code.
Until then, keep an eye on the repo and happy programming!
