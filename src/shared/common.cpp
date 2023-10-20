#include "common.h"
#include <cstddef>
#include <cstdint>
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

const char *B64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char PADDING = '=';

void buff_to_b64_str(const std::uint8_t *buff, std::size_t len, char **out) {
  // convert input string into uint8 buffer
  size_t buff_len;

  // b64 only use 6 bits, so we use each element of array to store 6 bits only
  // 11111111 11110000 11001100
  // __111111 __111111 __000011 __001100
  // or we can say 3 uint8 elements turn into 4 uint6 elements
  size_t b64_buff_len = buff_len * 8 / 6;
  *out = (char *)std::malloc(b64_buff_len * sizeof(char) + 1); // +1 for \0

  memset(*out, 0, b64_buff_len);
  int j = 0;
  for (int i = 0; i < buff_len; i += 3) {
    (*out)[j++] = B64_CHARS[buff[i + 0] >> 2];
    (*out)[j++] = B64_CHARS[((buff[i + 0] & 0b11) << 4) | (buff[i + 1] >> 4)];
    (*out)[j++] = B64_CHARS[((buff[i + 1] & 0b1111) << 2) | (buff[i + 2] >> 6)];
    (*out)[j++] = B64_CHARS[buff[i + 2] & 0b00111111];
  }
}

std::uint8_t single_b64_to_uint(char b64) {
  if (b64 == '+')
    return 62;
  if (b64 == '/')
    return 63;
  if (b64 < 'a')
    return b64 - 'A';
  return ('Z' - 'A') + 1 + b64 - 'a'; // a is Z+1
}

void b64_str_to_buff(const char *b64, std::uint8_t **buff,
                     std::size_t *bufflen) {
  std::size_t len = strlen(b64);
  std::size_t paddings = 0;
  while (b64[len - 1 - paddings] == '=')
    paddings++;
  (*bufflen) = (len - paddings) * 3 / 4;
  *buff = (std::uint8_t *)malloc(sizeof(std::uint8_t) * (*bufflen));
  // b64 __101010 __010101 __110011 __000111
  // ui8 10101001 01011100 11000111
  int miss = 0;
  std::uint8_t val;
  for (int i = 0; i < len; i++) {
    if (b64[i] == '=')
      break;
    val = single_b64_to_uint(b64[i]);
    if (miss) {
      (*buff)[i - 1] |= (val >> (6 - miss));
    }
    (*buff)[i] = (val << (miss + 2));
    miss = (miss + 2) % 8;
  }
  for (int i = 0; i < len; i++) {
    printf("x%2x ", (*buff)[i]);
  }
  printf("\n");
}
