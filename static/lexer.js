"use strict";

class TokenDef {
	constructor(regex, label) {
		this.regex = regex;
		this.label = label;
	}
}
class TokenList extends Array {
	constructor() {
		super();
	}
}
class Token {
	constructor(value, label) {
		this.value = value;
		this.label = label;
	}
}
//const definitions = rules.map(x => new TokenDef(x[0], x[1]));

const definitions = [
	[/^\t/,                         "indentation"],
	[/^\n/,                         "break"],
	[/^\s/,                         "whitespace"],
	[/^[a-zA-Z_]\w*/,               "identifier"],
	[/^[()[\]]/,                    "grouping"],
	[/^\/\/[^\n]*/,                 "singlelineComment"],
	[/^\/\*[^]*?\*\//,              "multilineComment"],
	[/^[+\-*\/%=&^|<>~!?:.$#@\\]+/, "operator"],
	[/^"(?:[^"\n\\]|\\.)*"/,        "string"],
	[/^\d+(?:\.\d+)?/,              "number"],
	[/^[^]/,                        "unrecognized"]
];
const lexer = text => {
	let tokens = new TokenList();
	let index = 0;
	while (index < text.length) {
		for (const [regex, label] of definitions) {
			const matches = text.match(regex, index);
			if (matches) {
				const match = matches[0];
				index += match.length;
				tokens.push(new Token(match, label));
				break;
			}
		}
	}
	return tokens;
};

lexer(`console.log(3.5 / 2, "Hello" + ", world"); // prints hello world`);
//const keywords = new Set("class uses if else for while do break continue switch return".split(" "));
//const constants = new Set("true false infinity pi twoPi e phi rootTwo".split(" "));
