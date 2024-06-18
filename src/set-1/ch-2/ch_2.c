#include "ch_2.h"

#include "common.h"
#include "fixed_xor.h"

int main() {
  const char* str = "1c0111001f010100061a024b53535009181c";
  const char* key = "686974207468652062756c6c277320657965";
  const char* expected = "746865206b696420646f6e277420706c6179";

  char* out;
  u_int8_t* buff_str;
  u_int8_t* buff_key;
  u_int8_t* buff_out;
  size_t len;
  size_t len_key;

  hex_str_to_buff(str, &buff_str, &len);
  hex_str_to_buff(key, &buff_key, &len_key);

  assert(len == len_key);

  fixed_xor(buff_str, buff_key, len, &buff_out);

  buff_to_hex_str(buff_out, len, &out);
  printf("%s\n", out);
  assert(strcmp(out, expected) == 0);
  free(buff_str);
  free(buff_key);
  free(buff_out);
  free(out);

  return 0;
}
