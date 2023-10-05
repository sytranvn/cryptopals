#ifndef CH_2_H_
#define CH_2_H_

#include "common.h"
#include <cstddef>
#include <cstdint>
#include <memory>

void fixed_xor(const char *str1, const char *str2, std::uint8_t **buff,
               std::size_t &len);

#endif
