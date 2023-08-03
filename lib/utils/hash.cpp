#include "hash.hpp"
#include <string.h>

#define SHA256_DIGEST_LENGTH 32

std::string sha256(char * str)
{
    unsigned char md[SHA256_DIGEST_LENGTH];
    EVP_Q_digest(NULL, "SHA256", NULL, str, strlen(str), md, NULL);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)md[i];
    return ss.str();
}