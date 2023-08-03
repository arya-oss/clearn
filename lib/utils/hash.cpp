#include "hash.hpp"

#define SHA256_DIGEST_LENGTH 32

std::string sha256(const std::string str)
{
    unsigned char md[SHA256_DIGEST_LENGTH];
    EVP_Q_digest(NULL, "SHA256", NULL, str.c_str(), str.size(), md, NULL);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)md[i];
    return ss.str();
}