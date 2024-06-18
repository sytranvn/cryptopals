#include "repeating_key_xor.h"

void repeating_key_xor(const char* str, const char* key, u_int8_t** out) {
  size_t slen = strlen(str);
  size_t klen = strlen(key);
  *out = malloc(slen * sizeof(u_int8_t));
  for (int i = 0; i < slen; i++) {
    (*out)[i] = str[i] ^ key[i % klen];
  }
}
