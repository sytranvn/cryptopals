#include "ch_3.h"

int main() {
  const char* str =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  char key;
  const char* expected = "Cooking MC's like a pound of bacon";

  u_int8_t* buff_str;
  char* out;
  size_t len;

  hex_str_to_buff(str, &buff_str, &len);
  single_byte_xor(buff_str, len, &out, &key);

  assert(strcmp(out, expected) == 0);
  free(buff_str);
  free(out);

  return 0;
}
