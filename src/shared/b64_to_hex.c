#include "b64_to_hex.h"

char* b64_to_hex(const char* b64) {
  u_int8_t* buff;
  size_t bufflen;
  buff = b64_str_to_buff(b64, &bufflen);
  char* hex = buff_to_hex_str(buff, bufflen);
  free(buff);
  return hex;
}
