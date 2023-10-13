#include "ch_5.h"
#include "common.h"
#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>

TEST(ch_5, repeating_key_xor) {
  char *out;
  char *hex;
  const char *str = "Burning 'em, if you ain't quick and nimble\n"
                    "I go crazy when I hear a cymbal";
  const char *key = "ICE";
  const char *expect = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343"
                       "c2a26226324272765272"
                       "a282b2f20430a652e2c652a3124333a653e2b2027630c692b202831"
                       "65286326302e27282f";

  char cipher;
  repeating_key_xor(str, key, &out);
  buff_to_hex_str((const std::uint8_t *)out, strlen(out), hex);
  ASSERT_STREQ(hex, expect);

  free(out);
  free(hex);
};
