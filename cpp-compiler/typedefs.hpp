#pragma once

#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int32_t i32;

typedef float f32;

void wait() {
	printf("press ENTER to continue...");
	getchar();
	printf("\n");
}
