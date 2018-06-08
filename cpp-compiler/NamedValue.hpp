#pragma once

enum NamedValueE {
	FunctionE,
	VariableE,
	TypeE
};

class NamedValue {
public:
	NamedValueE type;
};

class Function : NamedValue {
public:
	const NamedValueE type = FunctionE;
};

class Variable : NamedValue {
public:
	const NamedValueE type = VariableE;
};

class Type : NamedValue {
public:
	const NamedValueE type = TypeE;
};