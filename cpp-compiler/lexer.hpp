#pragma once

#include <vector>
#include "Token.hpp"
#include "VStream.hpp"
#include "typedefs.cpp"

std::vector<Token> lexer(VStream stream);