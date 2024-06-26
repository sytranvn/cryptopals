#include "ch_3.h"

#include <stdio.h>

int main() {
  const char* str =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  const char* expected = "Cooking MC's like a pound of bacon";

  char key;
  u_int8_t* buff_str;
  char* out;
  size_t len;
  float s;

  buff_str = hex_str_to_buff(str, &len);
  out = single_byte_xor(buff_str, len, &key, NULL);

  assert(strcmp(out, expected) == 0);
  printf("Key: %c\nMessage: %s\n", key, out);
  free(buff_str);
  free(out);

  return 0;
}
