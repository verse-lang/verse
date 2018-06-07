#pragma once

#include "IDGenerator.cpp"
#include "typedefs.cpp"

class StringTreeNode {
public:
	StringTreeNode * left;
	StringTreeNode* right;
	u8 midpoint;
	StringTreeNode() {
		left = nullptr;
		right = nullptr;
		midpoint = tempMidpoint;
	}
};

class StringTree {
public:
	UniformIDGenerator ids;
	StringLabelerNode root;
	u32 label(char *string) {
		//StringLabelerNode *cur;
		//while ()
	}
};