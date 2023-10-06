#include "ch_3.h"
#include "common.h"
#include <algorithm>
#include <cstring>
#include <string.h>

const char *most_freq = "etaoin shrdlu";
constexpr int most_freq_len = noexcept(strlen(most_freq));

bool compare(const char *a, const char *b) {
  if (strlen(a) < strlen(b))
    return true;
  else if (strlen(b) < strlen(a))
    return false;
  int ca, cb;
  for (int i = 0; i < most_freq_len; i++) {
    ca = 0;
    cb = 0;
    for (int j = 0; j < strlen(a); j++) {
      if (tolower(a[j]) == most_freq[i])
        ca++;
      if (tolower(b[j]) == most_freq[i])
        cb++;
    }
    if (ca < cb)
      return true;
    else if (cb < ca)
      return false;
  }
  return true;
};

// TODO: assign best value to cipher
// assign plain text to out
void single_byte_xor_cipher(const char *str, char **out, char *cipher) {
  std::uint8_t *buff;
  std::size_t len;

  hex_str_to_buff(str, buff, len);
  char **rs;
  rs = (char **)malloc(sizeof(char *) * (95)); // 127 (~) - 32 (space)
  for (std::uint8_t i = 0; i < 95; i++) {
    rs[i] = (char *)malloc(sizeof(char) * len + 1);
    char ch = i + 32;
    for (int j = 0; j < len; j++) {
      std::uint8_t r = ch ^ buff[j];
      if (r < 32 || r >= 127) {
        break;
      }
      rs[i][j] = r;
    }
    std::sort(rs, rs + 95, compare);
  }
  strcpy(*out, rs[0]);
  free(rs);
}
