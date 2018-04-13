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
	const u32 byteLen = unitSize * (array->cap <<= 1);
	array->data = (void *)realloc(array->data, byteLen);
	if (array->data == NULL) puts("out of memory when growing.");
}

typedef struct { // extends DynArray
	u32 cap;
	u32 length;
	Token *data; // array
} TokenDynArray;

#endif /* parseTools */
