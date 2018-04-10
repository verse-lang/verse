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
/*bool StreamMatchChar(Stream *this, char chr) {
	if (this->index < this->length && this[this->index] == chr) {
		this->index++;
		return true;
	}
	return false;
}
bool StreamMatchString(Stream *this, String *string) {
	u32 end = this->index + string->length;
	if (end > this.length) return false;
	while (n < string->length) {
		if (this->content[this->index] != string->content[n]) return false;
		this->index++;
		n++;
	}
	return true;
}
bool StreamMatchRange(Stream* this, char min, char max) {
	if (this->index >= this->length ||
		this->content[this->index] > max ||
		this->content[this->index] < min) return false;
	this->index++;
	return true;
}
void StreamMatchCharMany(Stream *this, char chr) {
	while (this->index < this->length && this->content[this->index] == chr) {
		this->index++;
	}
}
void StreamMatchStringMany(Stream *this, String *string) {
	u32 start;
	do {
		start = this->index;
	} while (StreamMatchString(this, string));
	this->index = start;
}*/

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
	Token* data; // array
} TokenDynArray;
void TokenDynArrayGrow(TokenDynArray *tokens) {
	const u32 byteLen = sizeof(Token) * (tokens->cap <<= 1);
	tokens->data = (Token*)realloc(tokens->data, byteLen);
	if (tokens->data == NULL) puts("out of memory when growing.");
	//printf("grown to %i\n", tokens->cap);
}

#endif /* parseTools */
