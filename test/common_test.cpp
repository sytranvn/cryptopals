#include "common.h"
#include <_types/_uint8_t.h>
#include <cstring>
#include <gtest/gtest.h>

TEST(common, hex_str_to_buff) {
  char *str =
      (char *)("49276d206b696c6c696e6720796f757220627261696e206c696b6520"
               "6120706f69736f6e6f7573206d757368726f6f6d\0");
  std::size_t len;
  std::uint8_t *buff;
  hex_str_to_buff(str, buff, len);
  ASSERT_EQ(len, strlen(str) / 2);
  ASSERT_EQ(buff[0], 0x49);
  free(buff);
}
TEST(common, buff_to_hex_str) {
  char *str;
  std::size_t len = 2;
  std::uint8_t buff[] = {0x49, 0x27};
  char *expect = (char *)"4927";
  buff_to_hex_str(buff, len, str);
  ASSERT_STREQ(str, expect);
  free(str);
}
