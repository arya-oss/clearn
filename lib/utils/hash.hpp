#ifndef __LIB_UTILS_HASH_HPP
#define __LIB_UTILS_HASH_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>

std::string sha256(const std::string str);

#endif // __LIB_UTILS_HASH_HPP