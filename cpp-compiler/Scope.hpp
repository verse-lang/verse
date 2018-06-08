#pragma once

#include "StringTree.hpp"
#include "HashMap.hpp"
#include "NamedValue.hpp"

class Scope {
public:
	StringTree strings;
	HashMap<NamedValue> map;
};