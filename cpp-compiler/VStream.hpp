#pragma once

#include "typedefs.hpp"

struct VStream {
	u8 *content;
	u32 length;
	u32 index;
};