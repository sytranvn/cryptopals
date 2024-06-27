#ifndef COMMON_H_
#define COMMON_H_
#define DEBUG 0

#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

u_int8_t *hex_str_to_buff(const char *str, size_t *len);
u_int8_t *b64_str_to_buff(const char *b64, size_t *bufflen);

char *buff_to_hex_str(const u_int8_t *buff, size_t len);
char *buff_to_b64_str(const u_int8_t *buff, size_t len);

void long_str_to_lines(const char *str, int max_len, char ***out, size_t *len);

void b64_str(const char *str, char **out);

/** My malloc*/
void *mmalloc(size_t size);

void *mcalloc(size_t nmem, size_t size, const char *_file, int _line);

u_int ipow(int base, u_int ex);
u_int64_t llpow(int base, u_int ex);

void *combinations(void *base, size_t nmem, size_t size);

#define debug(fmt, ...)                             \
  do {                                              \
    if (DEBUG) fprintf(stderr, fmt, ##__VA_ARGS__); \
  } while (0)

#endif
