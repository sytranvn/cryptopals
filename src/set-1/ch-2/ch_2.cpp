#include "ch_2.h"

void fixed_xor(const char *str1, const char *str2, std::uint8_t **buff,
               std::size_t &len) {
  std::uint8_t *buff1, *buff2;
  std::size_t len1, len2;

  hex_str_to_buff(str1, buff2, len1);
  hex_str_to_buff(str2, buff2, len2);
  *buff = (std::uint8_t *)malloc(sizeof(std::uint8_t) * len1);
  len = len1;
  for (int i = 0; i < len1; i++) {
    *buff[i] = (buff1[i]) ^ (buff2[i]);
  }
}
