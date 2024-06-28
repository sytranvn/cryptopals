#include "common.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const char *B64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\0";
const char PADDING = '=';

void b64_str(const char *str, char **out) {
  // convert input string into uint8 buffer
  size_t buff_len;
  u_int8_t *buff = hex_str_to_buff(str, &buff_len);

  // b64 only use 6 bits, so we use each element of array to store 6 bits only
  // 11111111 11110000 11001100
  // __111111 __111111 __000011 __001100
  // or we can say 3 uint8 elements turn into 4 uint6 elements
  size_t b64_buff_len = buff_len * 8 / 6;
  *out = (char *)malloc(b64_buff_len * sizeof(char) + 1);  // +1 for \0

  memset(*out, 0, b64_buff_len);
  int j = 0;
  for (int i = 0; i < buff_len; i += 3) {
    (*out)[j++] = B64_CHARS[buff[i + 0] >> 2];
    (*out)[j++] = B64_CHARS[((buff[i + 0] & 0b11) << 4) | (buff[i + 1] >> 4)];
    (*out)[j++] = B64_CHARS[((buff[i + 1] & 0b1111) << 2) | (buff[i + 2] >> 6)];
    (*out)[j++] = B64_CHARS[buff[i + 2] & 0b00111111];
  }
}
/**
 * @param[in] str hex string to convert to buffer
 * @param[out] buff buffer
 */
u_int8_t *hex_str_to_buff(const char *str, size_t *len) {
  char *a;
  int l = strlen(str);
  assert(l % 2 == 0);
  a = (char *)mmalloc(l * sizeof(char));
  for (int i = 0; i < l; i++) {
    assert((str[i] >= '0' && str[i] <= '9') ||
           (str[i] >= 'a' && str[i] <= 'f'));
    if (str[i] >= '0' && str[i] <= '9')
      a[i] = str[i] - '0';
    else
      a[i] = 10 + (str[i] - 'a');
  }
  u_int8_t *buff = (u_int8_t *)mmalloc((l / 2) * sizeof(u_int8_t));
  for (int i = 0; i < l / 2; i++) {
    buff[i] = 0;
    buff[i] |= ((a[i * 2] << 4) | a[i * 2 + 1]);
  }
  *len = l / 2;
  return buff;
}
char *buff_to_hex_str(const u_int8_t *buff, size_t len) {
  char *str = (char *)_mcalloc((len * 2 + 1), sizeof(char), __FILE__, __LINE__);
  char f, s;
  for (int i = 0; i < len; i++) {
    f = buff[i] >> 4;
    s = buff[i] & 0x0f;
    assert(f < 16);
    assert(s < 16);
    if (f > 9) {
      str[i * 2] = (f - 10) + 'a';
    } else {
      str[i * 2] = f + '0';
    }

    if (s > 9) {
      str[i * 2 + 1] = (s - 10) + 'a';
    } else {
      str[i * 2 + 1] = s + '0';
    }
  }
  return str;
}

void long_str_to_lines(const char *str, int max_len, char ***out, size_t *len) {
  char **strs;
  char line[100];
  char s;
  int col = 0;
  int row = 0;
  memset(line, '\0', 100);
  strs = (char **)malloc(sizeof(char *) * max_len);  // pointers are cheap

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

char *buff_to_b64_str(const u_int8_t *buff, size_t len) {
  // b64 only use 6 bits, so we use each element of array to store 6 bits only
  // buf i 11111111 11110000 11001100
  // b64 j __111111 __111111 __000011 __001100
  // or we can say 3 uint8 elements turn into 4 uint6 elements
  size_t b64_buff_len = len * 4 / 3;
  char *out = (char *)_mcalloc((b64_buff_len + 1), sizeof(char), __FILE__,
                               __LINE__);  // +1 for \0
  int j = 0;
  for (int i = 0; i < len; i += 3) {
    assert(i + 2 < len);
    out[j++] = B64_CHARS[buff[i + 0] >> 2];
    out[j++] = B64_CHARS[((buff[i + 0] & 0b11) << 4) | (buff[i + 1] >> 4)];
    out[j++] = B64_CHARS[((buff[i + 1] & 0b1111) << 2) | (buff[i + 2] >> 6)];
    out[j++] = B64_CHARS[buff[i + 2] & 0b00111111];
  }
  return out;
}

u_int8_t single_b64_to_uint(char b64) {
  if (b64 == '+') return 62;
  if (b64 == '/') return 63;
  if ('A' <= b64 && b64 <= 'Z') return b64 - 'A';
  if ('a' <= b64 && b64 <= 'z') return b64 - 'a' + 26;
  if ('0' <= b64 && b64 <= '9') return b64 - '0' + 52;
  return b64 - '0';
}

static int max(int a, int b) { return a > b ? a : b; }
static int min(int a, int b) { return a < b ? a : b; }

u_int8_t *b64_str_to_buff(const char *b64, size_t *bufflen) {
  size_t len = strlen(b64);
  size_t paddings = 0;
  while (b64[len - 1 - paddings] == '=') paddings++;
  assert(len % 4 == 0);
  (*bufflen) = (len - paddings) * 3 / 4;
  u_int8_t *buff =
      (u_int8_t *)_mcalloc(*bufflen, sizeof(u_int8_t), __FILE__, __LINE__);
  // b64 i __101010 __010101 __110011 __000111
  // ui8 j 10101001 01011100 11000111
  int j = 0;
  for (int i = 0; i < len; i += 4) {
    u_int8_t val0 = single_b64_to_uint(b64[i]);
    u_int8_t val1 = single_b64_to_uint(b64[i + 1]);
    u_int8_t val2 = single_b64_to_uint(b64[i + 2]);
    u_int8_t val3 = single_b64_to_uint(b64[i + 3]);
    assert(val0 < 64);
    assert(val1 < 64);
    assert(val2 < 64);
    assert(val3 < 64);

    buff[j] = (val0 << 2) | (val1 >> 4);

    buff[j + 1] = (val1 << 4) | (val2 >> 2);

    buff[j + 2] = (val2 << 6) | val3;
    int a, b, c;
    a = buff[j];
    b = buff[j + 1];
    c = buff[j + 2];

    j += 3;
  }
  return buff;
}

void *_mmalloc(size_t size, const char *_file, int _line) {
  void *p = malloc(size);
  if (!p) {
    fprintf(stderr, "[%s:%d]Unable to allocate %ld bytes\n", _file, _line,
            size);
    exit(EXIT_FAILURE);
  }
  return p;
}

void *_mcalloc(size_t nmem, size_t size, const char *_file, int _line) {
  void *p = calloc(nmem, size);
  if (!p) {
    fprintf(stderr, "[%s:%d] Unable to allocate %ld bytes\n", _file, _line,
            size);
    exit(EXIT_FAILURE);
  }
  return p;
}

u_int ipow(int base, u_int ex) {
  unsigned result = 1;
  while (ex) {
    if (ex % 2) result *= base;
    ex /= 2;
    base *= base;
  }
  return result;
}

u_int64_t llpow(int base, u_int ex) {
  u_int64_t result = 1;
  u_int64_t b = (u_int64_t)base;
  while (ex) {
    if (ex % 2) result *= b;
    ex /= 2;
    b *= b;
  }
  return result;
}
