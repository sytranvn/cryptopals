#include <gtest/gtest.h>

#include "ch_2.h"
#include "common.h"

TEST(ch_2, fixed_xor) {

  char *str1 = (char *)("1c0111001f010100061a024b53535009181c");
  char *str2 = (char *)("686974207468652062756c6c277320657965");
  char *expect = (char *)"746865206b696420646f6e277420706c6179";
  std::uint8_t *out;
  std::size_t len;
  fixed_xor(str1, str2, &out, len);
  char *outstr;
  buff_to_hex_str(out, len, outstr);
  ASSERT_STREQ(outstr, expect);

  free(out);
  free(outstr);
}
