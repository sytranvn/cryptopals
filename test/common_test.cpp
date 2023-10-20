#include "common.h"
#include <cstddef>
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

TEST(common, hamming_distance) {
  const char *str = "this is a test";
  const char *str2 = "wokka wokka!!!";
  ASSERT_EQ(hamming_distance(str, str2, strlen(str)), 37);
}

TEST(common, b64_to_buff_A_to_Z) {
  const char *b64 = "AAZZ";
  const std::uint8_t expected[]{0x00, 0x06, 0x59};
  std::uint8_t *buff;
  std::size_t len;
  b64_str_to_buff(b64, &buff, &len);
  ASSERT_EQ(len, 3);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(buff[i], expected[i]);
  }
}

TEST(common, b64_to_buff_a_to_z) {
  const char *b64 = "adgz";
  const std::uint8_t expected[]{0x69, 0xd8, 0x33};
  std::uint8_t *buff;
  std::size_t len;
  b64_str_to_buff(b64, &buff, &len);
  ASSERT_EQ(len, 3);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(buff[i], expected[i]);
  }
}

TEST(common, b64_to_buff_padding) {
  const char *b64 = "kQz=";
  const std::uint8_t expected[]{0x91, 0x0c};
  std::uint8_t *buff;
  std::size_t len;
  b64_str_to_buff(b64, &buff, &len);
  ASSERT_EQ(len, 2);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(buff[i], expected[i]);
  }
}
TEST(common, b64_to_buff_padding_2) {
  const char *b64 = "kz==";
  const std::uint8_t expected[]{0x93};
  std::uint8_t *buff;
  std::size_t len;
  b64_str_to_buff(b64, &buff, &len);
  ASSERT_EQ(len, 1);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(buff[i], expected[i]);
  }
}
