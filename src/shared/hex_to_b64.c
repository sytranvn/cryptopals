#include "hex_to_b64.h"

void hex_to_b64(const char *hex_str, char **out) {
  u_int8_t *buff;
  size_t len;

  hex_str_to_buff(hex_str, &buff, &len);
  buff_to_b64_str(buff, len, out);
  free(buff);
}
