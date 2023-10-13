#include "ch_5.h"

void repeating_key_xor(const char *str, const char *key, char **out) {
  int len = strlen(str);
  int key_len = strlen(key);
  *out = (char *)malloc(sizeof(char) * (len + 1));
  (*out)[len - 1] = '\0';
  for (int i = 0; i < len; i++) {
    (*out)[i] = str[i] ^ (key[i % key_len]);
  }
}
