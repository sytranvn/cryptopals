#ifndef COMMON_H_
#define COMMON_H_
#include <cstddef>
#include <cstring>
#include <memory>
#include <sstream>

void hex_str_to_buff(const char *str, std::uint8_t *&buff, std::size_t &len);
void buff_to_hex_str(const std::uint8_t *buff, std::size_t len, char *&str);

#endif
