#include "common.h"
#include <cstring>

/**
 * @param[in] str hex string to convert to buffer
 * @param[out] buff buffer
 */
void hex_str_to_buff(const char *str, std::uint8_t *&buff, std::size_t &len) {
  unsigned int val;
  std::stringstream *ss = new std::stringstream;
  size_t l = strlen(str);
  len = l / 2;
  buff = (uint8_t *)malloc(sizeof(char) * len);
  int j = 0;
  for (int i = 0; i < strlen(str); i += 2) {
    (*ss) << str[i];
    (*ss) << str[i + 1];
    (*ss) >> std::hex >> val;
    buff[j++] = val;
    std::stringstream().swap(*ss);
    debug("%02x", val);
  }
  debug("\n");
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

void long_str_to_lines(const char *str, int max_len, char ***out,
                       std::size_t *len) {
  char **strs;
  char line[100];
  char s;
  int col = 0;
  int row = 0;
  memset(line, '\0', 100);
  strs = (char **)malloc(sizeof(char *) * max_len); // pointers are cheap

  for (char ch = *str; ch != '\0' && row < max_len; ch = *(++str)) {
    if (ch == '\n') {
      if (col > 0) {
        strs[row] = (char *)malloc(sizeof(char) * (col + 1));
        strcpy(strs[row], line);
        memset(line, '\0', 100);
        row++;
        col = 0;
      }
    } else {
      line[col] = ch;
      col++;
    }
  }
  if (row == max_len) {
    for (int i = 0; i < max_len; i++) {
      free(*strs);
    }
    free(strs);
    debug("ERROR: data is greater than max_len, consider increasing it");
    exit(1);
  } else {
    (*out) = (char **)malloc(sizeof(char *) * (row));

    for (int i = 0; i < row; i++) {
      (*out)[i] = strs[i];
    }
    free(strs);
    *len = row;
  }
}

int hamming_distance(const char *a, const char *b, std::size_t len) {
  int d = 0;
  for (int i = 0; i < len; i++) {
    d += __builtin_popcount(a[i] ^ b[i]);
  }
  return d;
}
