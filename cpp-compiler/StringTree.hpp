#pragma once

#include "IDGenerator.hpp"
#include "typedefs.cpp"

const u8 tempMidpoint = 76;
class StringTreeNode {
public:
	StringTreeNode * left;
	StringTreeNode* right;
	u8 midpoint;
	StringTreeNode();
};
class StringTree {
public:
	IDGenerator ids;
	StringTreeNode root;
	u32 label(char *string);
};