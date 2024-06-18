#include "fixed_xor.h"

#include <stdio.h>

void fixed_xor(const u_int8_t* buff, const u_int8_t* key, size_t len,
               u_int8_t** out) {
  *out = (u_int8_t*)malloc(len * sizeof(u_int8_t));
  if (!(*out)) {
    fprintf(stderr, "Unable to allocate %ld bytes\n", len * sizeof(u_int8_t));
  }

  for (int i = 0; i < len; i++) {
    (*out)[i] = buff[i] ^ key[i];
  }
};
