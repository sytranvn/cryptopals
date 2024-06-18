#include "ch_5.h"

#include <stdio.h>

const char* str =
    "Burning 'em, if you ain't quick and nimble\n"
    "I go crazy when I hear a cymbal";
const char* key = "ICE";
const char* expected =
    "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d6"
    "3343c2a26226324272765272a282b2f20430a652e2c652a3124"
    "333a653e2b2027630c692b20283165286326302e27282f";
u_int8_t* buff;
char* out;

int main() {
  repeating_key_xor(str, key, &buff);
  buff_to_hex_str(buff, strlen(str), &out);
  printf("%s\n", out);
  assert(strcmp(out, expected) == 0);
  return 0;
}
