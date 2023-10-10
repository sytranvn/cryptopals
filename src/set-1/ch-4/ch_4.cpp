#include "ch_4.h"
#include "common.h"

void detect_single_byte_xor(const char ***strs, std::size_t strs_len,
                            char **out, char *cipher) {
  char *cur;
  char cur_cipher;
  float fitness;
  float fitness_max = 0;

  for (int i = 0; i < strs_len; i++) {
    single_byte_xor_cipher((*strs)[i], &cur, &cur_cipher, &fitness);
    if (fitness > fitness_max) {
      std::strcpy(*out, (*strs)[i]);
      *cipher = cur_cipher;
    }
  }
}
