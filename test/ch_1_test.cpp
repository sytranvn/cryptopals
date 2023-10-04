#include <cstdio>
#include <gtest/gtest.h>

#include "ch_1.h"

TEST(ch_1, b64_str) {

  char *st = (char *)("49276d206b696c6c696e6720796f757220627261696e206c696b6520"
                      "6120706f69736f6e6f7573206d757368726f6f6d");
  char *expect =
      (char *)"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11"
              "c2hyb29t";
  char *out;
  b64_str(st, &out);

  ASSERT_STREQ(expect, out);

  free(out);
}
