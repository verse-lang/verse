const TokenList = class extends Array {
	constructor() {
		super();
		this.index = -1;
		this.cur = null;
		this.line = 1;
	}
	next() {
		if (this.index + 1 == this.length) {
			this.error("unexpected end of input");
		}
		this.cur = this[++this.index];
		//console.log(this.cur);
		if (this.cur.label == "break") {
			this.line++;
		}
		return this.cur;
	}
	backTo(index) {
		tokens.index = index - 1;
		tokens.next();
	}
	error(msg) {
		throw msg + "\n" + "Line: " + this.line;
	}
	/*checkBreak(msg) {
		if (this.cur.label != "break") {
			this.expected("line break after " + msg, this.cur.label + " " + this.cur.value);
		}
	}*/
	expected(a, b) {
		this.error("expected " + a + ", instead got: " + b);
	}
	checkType(type) {
		if (this.cur.label != type) {
			this.expected("type " + type, this.cur.label + " " + this.cur.value);
		}
	}
	checkValue(val) {
		if (this.cur.value != val) {
			//console.log(this.cur);
			this.expected("value " + val, this.cur.value);
		}
	}
	/*indexOfType(type) {
		let index = this.index;
		while (index < this.length && this[index].label != type) {
			index++;
		}
		return index == this.length ? -1 : index;
	}*/
};
const Token = class {
	constructor(value, label) {
		this.value = value;
		this.label = label;
	}
};
/*const Block = class {
	constructor(head, body) {
		this.head = head;
		this.body = body;
	}
};*/
const Assignment = class {
	constructor(type, assignee, value) {
		this.type = type;
		this.assignee = assignee;
		this.value = value;
	};
};
const Scope = class {
	constructor() {
		this.namespace = new Set();
		this.statements = [];
	}
};
/*const If = class extends Scope {
	constructor(condition, next) {
		super();
		this.condition = condition;
		this.next = next;
	};
}
const For = class extends Scope {
	constructor(init, modifier) {
		super();
		this.init = init;
		this.condition = condition;
		this.modifier = modifier;
	};
}
const While = class extends Scope {
	constructor(condition) {
		super();
		this.condition = condition;
	};
}
const Switch = class extends Scope {
	constructor(expression) {
		super();
		this.expression = expression;

	};
}*/
const Function = class extends Scope {
	constructor(name) {
		super();
		this.name = name;
		this.args = new Set();
	}
	/*concat(func) {
		for (const arg of func.args) {
			this.args.add(arg);
		}
		for (const stmt of func.statements) {
			this.statements.push(stmt);
		}
	}*/
};
const Method = class extends Function {
	constructor(name) {
		super(name);
		this.copyProps = 0;
	}
};
const Class = class extends Method {
	constructor(name) {
		super(name);
		this.props = new Set();
		this.methods = new Map();
		this.implements = new Set();
	}
	/*addProp(name, value) {
		this.props.add(name);
		this.statements.push();
	}
	concat(ic) {
		for (const arg of ic.args.values()) {
			cc.args.set(arg);
		}
		for (const mthd of ic.methods.values()) {
			let ccMthd = cc.methods.get(mthd.name);
			if (!ccMthd) {
				ccMthd = new Function(mthd.name);
				cc.methods.set(mthd.name)
			}
			ccMthd.concat(mthd);
		}
	}*/
};

const definitions = [
	[/^(?:\t|	)/,				   "indentation"],
	[/^\n/,							"break"],
	[/^\s/,							"whitespace"],
	[/^[a-zA-Z_]\w*/,				  "identifier"],
	[/^[()[\]]/,					   "grouping"],
	[/^\/\/[^\n]*/,					"singlelineComment"],
	[/^[+\-\/*%=&^|<>~!?:.$#@]+/,	  "operator"],
	[/^"(?:[^"\n\\]|\\[^])*"/,		 "string"],
	[/^\d+(?:\.\d+)?/,				 "number"],
	[/^\/\*[^]*?\*\//,				 "multilineComment"],
	[/^[^]/,						   "unrecognized"]
];
//const keywords = new Set("class uses if else for while do break continue switch return".split(" "));
//const constants = new Set("true false infinity pi twoPi e phi rootTwo".split(" "));

const lexer = text => {
	let tokens = new TokenList();
	while(text.length) {
		for (const [regex, label] of definitions) {
			const matches = text.match(regex);
			const match = matches && matches[0];
			if (match) {
				text = text.slice(match.length);
				tokens.push(new Token(match, label));
				break;
			}
		}
	}
	return tokens;
};
const ast = tokens => {
	const lines = text.split(a => a.label == "break");
	const root = new Scope();
	let curScope = root;
	let scopeStack = [];
	let curClass = null;
	let indentation = 0;
	let line = 0;
	for (const line of lines) {
		line++;
		let n = 0;
		while (n < line.length && line[n].label == "indentation") {
			n++;
		}
		let dif = n - indentation;
		if (dif > 1) {
			throw new Error("More than one indentation level.\nLine: " + line);
		}
		while(dif < 0) {
			curScope = scopeStack.pop();
			dif++;
		}
		const first = line[0];
		const val = first.value;
		if (val == "class") {
			scopeStack.push(curScope);
			const name = line[1];
			if (name.label != "identifier") {
				throw new Error("Expected an identifier after keyword (class).\nLine: " + line);
			}
			curClass = curScope = new Class(name.value);
			for (let n = 2; n < line.length; n++) {
				const cur = line[n];
				if (cur.label != "identifier") {
					throw new Error("Expected an indentifier in argument list.\nLine: " + line);
				}
				if (curClass.args.has(cur.value)) {
					throw new Error("Duplicate class argument \"" + cur.value + "\".\nLine: " + line);
				}
				curClass.args.add(cur.value);
			}
		} else if (val == "if") {
			curScope = new If(line.slice());
		} else if (val == "while") {

		} else if (val == "@") {

		} else if (val == "$") {

		} else if (val == "#") {

		} else {
			const second = line[1];

		}
	}
};
/*const indentationToBrackets = tokens => {
	let level = 0;
	for (let n = 0; n < tokens.length; n++) {
		const token = tokens[n];
		if (token.label == "indentation") {
			for (let i = n + 1, token = tokens[i]; i < tokens.length && token.label == "indentation"; i++);
			const newLevel = (i - n);
			if (newLevel > level) {

			} else {

			}
		}
	}
};*/
const removeWhitespace = tokens => {
	for (let n = 0; n < tokens.length; n++) {
		const token = tokens[n];
		if (token.label == "whitespace") {
			tokens.splice(n--, 1);
		}
	}
};
const joinOperators = tokens => {
	let a = tokens[0], b;
	for (let n = 1; n < tokens.length;) {
		b = tokens[n];
		if (a.label == "operator" && b.label == "operator") {
			a.value += tokens.splice(n, 1).value;
		} else {
			a = b;
			n++;
		}
	}
};
const readArgs = (tokens, mthd, args) => {
	let pipe = false;
	while (true) {
		if (tokens.next().label != "identifier") {
			if (!pipe && tokens.cur.value == "|") {
				pipe = true;
				mthd.copyProps = args.length;
				continue;
			}
		}
		if (args.has(tokens.cur.value)) {
			tokens.error(mthd.name + " already has argument: " + tokens.cur.value);
		}
		args.add(tokens.cur.value);
	}
};
const readImplements = (tokens, cc) => {
	while(tokens.next().label == "identifier") {
		const ic = classes.get(tokens.cur.value);
		if (!ic) {
			tokens.error("attempted to implement undeclared class: " + tokens.cur.value);
		}
		if (ic == cc) {
			tokens.error(cc.name + " attempted to implement itself");
		}
		cc.inmplements.push(ic);
	}
	tokens.checkBreak("implements list");
};
const readProperties = (tokens, cc) => {
	let start;
	let name;
	while ((start = tokens.index, true) && (name = tokens.next()).label == "identifier" && tokens.next().value == ":") {
		tokens.checkType("identifier");
		tokens.next();
		token.checkValue("=");
		let propValue = [];
		while(tokens.next().label != "break") {
			propValue.push(tokens.cur);
		}
		cc.addProp(2, propName, propValue);
	}
	tokens.index = start - 1;
	tokens.next();
};
const readMethods = (tokens, cc) => {
	let start;
	let name;
	while ((start = tokens.index, true) && (name = tokens.next()).label == "identifier" && tokens.next().value == "=>") {
		const mthd = new Method(name);
		readArgs(tokens, mthd, mthd.args);
	}
	tokens.back(start);
};
const ast = tokens => {
	tokens.next();
	removeWhitespace(tokens);
	joinOperators(tokens);
	let root = new Scope();
	let currentScope = root;
	let stack = [currentScope];
	let statement = [];
	let line = 1;
	let level = 0;
	for (let n = 0; n < tokens.length; n++) {
		const token = tokens[n];
		if (token.label == "break") {
			line++;
			let newLevel = 0;
			n++;
			while (n < tokens.length && tokens[i].label == "indentation") {
				n++;
				newLevel++;
			}
			n--;
			if (newLevel > level + 1) {
				throw new Error("More than one indentation level on one line.\nLine: " + line);
			} else if (newLevel > level) {
				level = newLevel;
				const nextToken = tokens[n + 1];
				if (nextToken.value == "class") {

				} else {

				}
			} else {
				currentScope.statements.push(readStatement(tokens, n));
			}
			statement = [];
		} else {
			statement.push(token);
		}
	}
	/*const classes = new Map();
	while (tokens.index < tokens.length) {
		tokens.checkValue("class");
		let cc = new Class(tokens.next());
		tokens.checkType("identifier");
		if (classes.has(cc.name)) {
			tokens.error(cc.name + " is already defined");
		}
		classes.set(cc.name, cc);
		readArgs(tokens, cc, cc.ownArgs);
		tokens.checkBreak("class argument list");
		if (tokens.next().value == "^^") {
			readImplements(tokens, cc);
		}
		readProperties(tokens, cc);
		readMethods(tokens, cc);
		/*if (tokens.next().value == "cprops") {
			tokens.next();
			tokens.checkType("number");
			if (!/^\d*$/.test(tokens.cur.value) || tokens.cur.value == "0") {
				tokens.expected("a positive integer", tokens.cur.value);
			}
			const cprops = parseInt(tokens.cur.value);
			const args = cc.ownArgs.values();
			if (cprops > args.length) {
				tokens.error(`cprops value: (${tokens.cur.value}), cannot be larger than ${cc.name}'s own args length (${args.length})`);
			}
			for (let n = cprops - 1; n >= 0; n--) {
				tokens.splice(tokens.index + 1, 0, ...lexer(`@${args[n]}=${args[n]}\n`));
			}
			tokens.next();
			tokens.checkBreak("cprops");
		}*!/
	}
	return classes;*/
};
const compile = classes => {
	let compiled = "";
	for (const clss of classes) {
		for (const implemented of clss.implements) {
			clss.concat(implemented);
		}
		let ownArgsArray = [];
		for (const arg of clss.ownArgs) {
			clss.args.add(arg);
			ownArgsArray.push(arg);
		}
		for (let n = 0; n < clss.copyProps; n++) {
			const arg = ownArgsArray[n];

		}
		compiled += clss.toJS();
	}
};
export const parse = text => compile(ast(lexer(text.trim())));

/*[
	["^[#$],identifier,^=,!break*", "declaration"],
	["identifier,^:,!break*", "instance"],
	["", "class"]
]*/
