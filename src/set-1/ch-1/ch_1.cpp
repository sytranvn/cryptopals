#include "ch_1.h"
#include <cstring>

const char *MY_B64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\0";
char *b64_str(const char *str) {
  printf("Print str: %s\n", str);
  std::uint8_t *buff;
  char *out;
  size_t buff_len;
  str_to_buff(str, buff, buff_len);
  // we only use 6 bits per element
  size_t b64_buff_len = ((sizeof(std::uint8_t) * buff_len + 5) / 6);
  std::uint8_t *b64_buff =
      (std::uint8_t *)std::malloc(b64_buff_len * sizeof(std::uint8_t));
  out = (char *)std::malloc(b64_buff_len * sizeof(char));

  memset(b64_buff, 0, b64_buff_len);
  memset(out, 0, b64_buff_len);

  for (int i = 0; i < buff_len; i += 4) {
    b64_buff[i + 0] = buff[i + 0] >> 2;
    printf("%c", MY_B64_CHARS[b64_buff[i + 0]]);
    b64_buff[i + 1] = ((buff[i + 0] & 0b11) << 4) & (buff[i + 1] >> 4);
    printf("%c", MY_B64_CHARS[b64_buff[i + 1]]);
    b64_buff[i + 2] = ((buff[i + 1] & 0b1111) << 2) & (buff[i + 2] >> 6);
    printf("%c", MY_B64_CHARS[b64_buff[i + 2]]);
    b64_buff[i + 3] = (buff[i + 2] << 2) >> 2;
    printf("%c", MY_B64_CHARS[b64_buff[i + 3]]);
  }
  return out;
}

// 10101010 00110011 11110000
// 101010 100011 001111 110000
