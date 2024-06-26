#include "hex_to_b64.h"

char* hex_to_b64(const char* hex_str) {
  u_int8_t* buff;
  size_t len;
  char* out;

  buff = hex_str_to_buff(hex_str, &len);
  out = buff_to_b64_str(buff, len);

  free(buff);

  return out;
}
