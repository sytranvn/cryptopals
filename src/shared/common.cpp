#include "common.h"
#include <malloc/_malloc.h>

/**
 * @param[in] str hex string to convert to buffer
 * @param[out] buff buffer
 */
void hex_str_to_buff(const char *str, std::uint8_t *&buff, std::size_t &len) {
  unsigned int val;
  std::stringstream *ss = new std::stringstream;
  size_t l = strlen(str);
  len = l / 2;
  buff = (uint8_t *)malloc(sizeof(char) * l / 2);
  for (int i = 0; i < strlen(str); i += 2) {
    (*ss) << str[i];
    (*ss) << str[i + 1];
    (*ss) >> std::hex >> val;
    buff[i / 2] = val;
    std::stringstream().swap(*ss);
  }
}

void buff_to_hex_str(const std::uint8_t *buff, std::size_t len, char *&str) {
  constexpr char *hexdigits = (char *)"0123456789abcdef";
  str = (char *)malloc(sizeof(char) * (len * 2 + 1));
  int j = 0;
  for (int i = 0; i < len; i++) {
    str[j++] = hexdigits[buff[i] >> 4];
    str[j++] = hexdigits[buff[i] & 0b1111];
  }
}
