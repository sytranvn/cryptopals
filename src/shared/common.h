#ifndef COMMON_H_
#define COMMON_H_
#define DEBUG 0

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void hex_str_to_buff(const char *str, u_int8_t **buff, size_t *len);
void buff_to_hex_str(const u_int8_t *buff, size_t len, char **str);
void long_str_to_lines(const char *str, int max_len, char ***out, size_t *len);

void b64_str(const char *str, char **out);
void b64_str_to_buff(const char *b64, u_int8_t **buff, size_t *bufflen);

void buff_to_b64_str(const u_int8_t *buff, size_t len, char **out);

#define debug(fmt, ...)                             \
  do {                                              \
    if (DEBUG) fprintf(stderr, fmt, ##__VA_ARGS__); \
  } while (0)

#endif
