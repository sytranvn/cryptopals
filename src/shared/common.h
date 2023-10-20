#ifndef COMMON_H_
#define COMMON_H_
#define DEBUG 0

#include <cstddef>
#include <cstring>
#include <sstream>
#include <stdlib.h>

void hex_str_to_buff(const char *str, std::uint8_t *&buff, std::size_t &len);
void buff_to_hex_str(const std::uint8_t *buff, std::size_t len, char *&str);
void long_str_to_lines(const char *str, int max_len, char ***out,
                       std::size_t *len);

int hamming_distance(const char *a, const char *b, std::size_t len);
void b64_str_to_buff(const char *b64, std::uint8_t **buff,
                     std::size_t *bufflen);

void buff_to_b64_str(const std::uint8_t *buff, std::size_t len, char **out);

#define debug(fmt, ...)                                                        \
  do {                                                                         \
    if (DEBUG)                                                                 \
      fprintf(stderr, fmt, ##__VA_ARGS__);                                     \
  } while (0)
#endif
