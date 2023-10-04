#include "common.h"
#include <gtest/gtest.h>

TEST(common, str_to_buff) {
  char *str =
      (char *)("49276d206b696c6c696e6720796f757220627261696e206c696b6520"
               "6120706f69736f6e6f7573206d757368726f6f6d\0");
  std::size_t len;
  std::uint8_t *buff;
  str_to_buff(str, buff, len);
  ASSERT_EQ(len, strlen(str) / 2);
  ASSERT_EQ(buff[0], 0x49);
  free(buff);
  free(str);
}
