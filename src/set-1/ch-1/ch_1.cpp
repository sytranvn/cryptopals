#include "ch_1.h"
#include <cstring>

const char *MY_B64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\0";

void b64_str(const char *str, char **out) {
  // convert input string into uint8 buffer
  std::uint8_t *buff;
  size_t buff_len;
  str_to_buff(str, buff, buff_len);

  // b64 only use 6 bits, so we use each element of array to store 6 bits only
  // 11111111 11110000 11001100
  // __111111 __111111 __000011 __001100
  // or we can say 3 uint8 elements turn into 4 uint6 elements
  size_t b64_buff_len = buff_len * 8 / 6;
  *out = (char *)std::malloc(b64_buff_len * sizeof(char) + 1); // +1 for \0

  memset(*out, 0, b64_buff_len);
  int j = 0;
  for (int i = 0; i < buff_len; i += 3) {
    (*out)[j++] = MY_B64_CHARS[buff[i + 0] >> 2];
    (*out)[j++] =
        MY_B64_CHARS[((buff[i + 0] & 0b11) << 4) | (buff[i + 1] >> 4)];
    (*out)[j++] =
        MY_B64_CHARS[((buff[i + 1] & 0b1111) << 2) | (buff[i + 2] >> 6)];
    (*out)[j++] = MY_B64_CHARS[buff[i + 2] & 0b00111111];
  }
}
