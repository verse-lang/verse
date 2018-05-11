#ifndef parseTools
#define parseTools

#include <stdio.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef u8 bool;
#define true 1
#define false 0

typedef struct {
	char *content;
	u32 length;
} String;

typedef struct { // extends String
	char *content;
	u32 length;
	u32 index;
} Stream;

typedef struct {
	u32 begin;
	u32 end;
} Match;

typedef struct { // extends Match
	u32 begin;
	u32 end;
	u8 id;
} Token;

typedef struct {
	u32 cap;
	u32 length;
	void *data;
} DynArray;
void DynArrayGrow(DynArray *array, const u32 unitSize) {
	const u32 byteLen = unitSize * (array->cap *= 2);
	array->data = (void *)realloc(array->data, byteLen);
	if (array->data == NULL) puts("out of memory when growing.");
}

typedef struct { // extends DynArray
	u32 cap;
	u32 length;
	Token *data; // array
} TokenDynArray;
void TokenDynArrayPrint(TokenDynArray tokens, char *content) {
	printf("length: %i, capacity: %i\n\n", tokens.length, tokens.cap);
	for (u32 n = 0; n < tokens.length; n++) {
		const Token cur = tokens.data[n];
		const char c = content[cur.end];
		content[cur.end] = '\0';
		printf("%i, `%s`\n", cur.id, content + cur.begin * sizeof(char));
		content[cur.end] = c;
	}
}

const u32 unusedID = 4294967295;
typedef struct {
	u32 step;
	u32 maxIndex;
	u32 index;
} UniformIDGenerator;
UniformIDGenerator newUniformIDGenerator() {
	UniformIDGenerator this;
	this.step = 2147483647;
	this.maxIndex = 1;
	this.index = 0;
}
u32 UniformIDGeneratorNext(UniformIDGenerator *this) {
	if (this->index >= this->maxIndex) {
		if (this->step == 1) {
			printf("out of possible ids\n");
			exit(1);
		}
		this->step /= 2;
		this->maxIndex *= 2;
		this->index = 0;
	}
	return ((this->index++) * 2 + 1) * this->step;
}

const tempMidpoint = 76;
typedef struct StringLabelerNode {
	struct StringLabelerNode* less;
	struct StringLabelerNode* more;
	u8 midpoint;
} StringLabelerNode;
StringLabelerNode newStringLabelerNode() {
	StringLabelerNode this;
	this.less = NULL;
	this.more = NULL;
	this.midpoint = tempMidpoint;
	
	return this;
}

typedef struct {
	UniformIDGenerator ids;
	StringLabelerNode root;
} StringLabeler;
u32 StringLabelerLabel(char *string) {
	StringLabelerNode *cur;
	while()
}

#endif /* parseTools */
