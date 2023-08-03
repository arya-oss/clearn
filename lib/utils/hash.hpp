#ifndef __LIB_UTILS_HASH_HPP
#define __LIB_UTILS_HASH_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h>

std::string sha256(char * str);

#endif // __LIB_UTILS_HASH_HPP