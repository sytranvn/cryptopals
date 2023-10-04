#include "common.h"

/**
 * @param[in] str hex string to convert to buffer
 * @param[out] buff buffer
 */
void str_to_buff(const char *str, std::uint8_t *&buff, std::size_t &len) {
  unsigned int val;
  std::stringstream *ss = new std::stringstream;
  size_t l = strlen(str);
  buff = (uint8_t *)malloc(sizeof(char) * l / 2);
  printf("Input ");
  for (int i = 0; i < strlen(str); i += 2) {
    (*ss) << str[i];
    (*ss) << str[i + 1];
    (*ss) >> std::hex >> val;
    buff[i / 2] = val;
    printf("%d ", val);
    std::stringstream().swap(*ss);
  }
  printf("\n");
  len = l / 2;
  for (int i = 0; i < len; i++) {
    printf("%x ", buff[i]);
  }
  printf("\n");
}
