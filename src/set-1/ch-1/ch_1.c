#include "ch_1.h"

#include <string.h>
#include <sys/types.h>

#include "common.h"

int main() {
  const char* str =
      "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e"
      "6f7573206d757368726f6f6d";
  const char* expected =
      "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

  char* out;
  hex_to_b64(str, &out);
  printf("%s\n", out);
  assert(strcmp(out, expected) == 0);

  u_int8_t* buff;
  size_t bufflen;
  char* hex_out;
  b64_str_to_buff(expected, &buff, &bufflen);
  buff_to_hex_str(buff, bufflen, &hex_out);

  assert(strcmp(str, hex_out) == 0);

  free(out);
  free(buff);
  free(hex_out);

  return 0;
}
