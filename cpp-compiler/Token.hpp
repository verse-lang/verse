#pragma once

#include "typedefs.hpp"
#include "Match.hpp"

enum TokenID : u8 {
	identifier,
	comment,
	oprtr,
	indent,
	groupDelim,
	eol,
	number,
	type,
	character,
	eof
};

class Token : public Match {
public:
	enum TokenID id;
};
