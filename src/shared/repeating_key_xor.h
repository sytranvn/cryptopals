#ifndef REPEATING_KEY_XOR_H_
#define REPEATING_KEY_XOR_H_

#include <stdlib.h>
#include <sys/types.h>

#include "common.h"

char* repeating_key_xor(const char* str, size_t len, const char* key);
#endif
