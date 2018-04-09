let n;
let tokens;
let token;

const Scope = class {
	constructor() {
		this.namespace = new Map();
		this.statements = [];
	}
};
const Variable = class {
	constructor(type, id) {
		this.type = type;
		this.id = id;
	}
};

const parser = tokensArg => {
	tokens = tokensArg;
	for (n = 0; n < tokens.length; n++) {
		token = tokens[n++];
		switch (token.label) {
			case "identifier":
				readFromIdentifier();
				break;
			case "operator":
				readFromOperator();
				break;
			default:
				readExpression();
				break;
		}
	}
};
const readFromIdentifier = () => {
	switch (token.value) {
		case "import":
			readImport();
			break;
		case "if":
			readIf();
			break;
		case "while":
			readWhile();
			break;
		case "for":
			readFor();
			break;
		case "struct":
			readStruct();
			break;
		case "class":
			readClass();
			break;
		default:
			readFromDefaultIdentifier();
			break;
	}
};
const readFromOperator = () => {
	// test for const declaration
	// else
	readFromExpression();
};
const readExpression = () => {
	// use SEBNF rule to generate parse tree
	// create AST from parse tree
};
const readFromDefaultIdentifier = () => {
	// test for declaration
	// else
	readExpression();
};
const readImport = () => {
	const next = tokens[n++];
	if (next.label == "string") {

	} else if (next.label == "identifier") {
		if (tokens[n++].value != "from") {
			comErr("expected keyword 'from' after import identifier.");
		}
		const source = tokens[n++];
		if (source.label != "string") {
			comErr("expected source path after keyword 'from'.");
		}
		
	}
};
