#ifndef FIXED_XOR_H_
#define FIXED_XOR_H_

#include "common.h"

void fixed_xor(const u_int8_t* buff, const u_int8_t* key, size_t len,
               u_int8_t** out);

#endif
