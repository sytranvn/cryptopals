#include "b64_to_hex.h"

void b64_to_hex(const char* b64, char** hex) {
  u_int8_t* buff;
  size_t bufflen;
  b64_str_to_buff(b64, &buff, &bufflen);
  buff_to_hex_str(buff, bufflen, hex);
  free(buff);
}
