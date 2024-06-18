#ifndef REPEATING_KEY_XOR_H_
#define REPEATING_KEY_XOR_H_

#include <stdlib.h>
#include <sys/types.h>

#include "common.h"
void repeating_key_xor(const char* str, const char* key, u_int8_t** out);

#endif
