#include "ch_3.h"
#include "common.h"

// https://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
// added 7.0 for space character
float freq_table[95]{
    7,    0,     0,    0,    0,    0,    0,    0,    0,    0,     0,    0,
    0,    0,     0,    0,    0,    0,    0,    0,    0,    0,     0,    0,
    0,    0,     0,    0,    0,    0,    0,    0,    0,    8.12,  1.49, 2.71,
    4.32, 12.02, 2.3,  2.03, 5.92, 7.31, 0.1,  0.69, 3.98, 2.61,  6.95, 7.68,
    1.82, 0.11,  6.02, 6.28, 9.1,  2.88, 1.11, 2.09, 0.17, 2.11,  0.07, 0,
    0,    0,     0,    0,    0,    8.12, 1.49, 2.71, 4.32, 12.02, 2.3,  2.03,
    5.92, 7.31,  0.1,  0.69, 3.98, 2.61, 6.95, 7.68, 1.82, 0.11,  6.02, 6.28,
    9.1,  2.88,  1.11, 2.09, 0.17, 2.11, 0.07, 0,    0,    0,     0};

int freq_of(const char *str) {
  float s = 0;
  for (int i = 0; i < strlen(str); i++) {
    s += freq_table[str[i] - 32];
  }
  return s;
}

void single_byte_xor_cipher(const char *str, char **out, char *cipher) {
  std::uint8_t *buff;
  std::size_t len;

  hex_str_to_buff(str, buff, len);
  char *cur = (char *)malloc(sizeof(char) * (len + 1));
  *out = (char *)malloc(sizeof(char) * (len + 1));
  float max_freq = 0;
  float freq_cur = 0;

  // try xor each printable character with current string
  for (std::uint8_t i = 0; i < 95; i++) {
    memset(cur, '\0', sizeof(char) * (len + 1));
    std::uint8_t ch = i + 32;

    for (int j = 0; j < len; j++) {
      std::uint8_t r = (std::uint8_t)ch ^ (std::uint8_t)buff[j];
      if (r < 32 || r >= 127) {
        break;
      }
      cur[j] = r;
    }
    freq_cur = freq_of(cur);
    if (freq_cur > max_freq) {
      max_freq = freq_cur;
      strcpy(*out, cur);
      *cipher = ch;
    }
  }

  free(cur);
}
