#include "repeating_key_xor.h"

char* repeating_key_xor(const char* str, size_t len, const char* key) {
  size_t klen = strlen(key);
  char* out = mmalloc(len * sizeof(u_int8_t));
  for (int i = 0; i < len; i++) {
    out[i] = str[i] ^ key[i % klen];
  }
  return out;
}
