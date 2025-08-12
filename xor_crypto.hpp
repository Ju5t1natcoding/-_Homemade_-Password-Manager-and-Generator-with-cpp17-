#pragma once
#include "util_crypto.hpp"

uint64_t mix_hash64(const string &s) {
    std::hash<string> h; return (uint64_t)h(s);
}

string xor_encrypt_blob(const string &plaintext, const string &master) {
    string salt = gen_salt_bytes(8);
    uint64_t seed = mix_hash64(master + salt);
    mt19937_64 rng(seed);

    string out;
    out.reserve(8 + plaintext.size());
    out.append(salt);

    for (size_t i = 0; i < plaintext.size(); ++i) {
        unsigned char kb = (unsigned char)(rng() & 0xFF);
        out.push_back(char((unsigned char)plaintext[i] ^ kb));
    }

    return out;
}

string xor_decrypt_blob(const string &blob, const string &master) {
    if (blob.size() < 8) {
        return "";
    }

    string salt = blob.substr(0,8);
    string cipher = blob.substr(8);
    uint64_t seed = mix_hash64(master + salt);
    mt19937_64 rng(seed);
    string out; out.resize(cipher.size());

    for (size_t i = 0; i < cipher.size(); ++i) {
        unsigned char kb = (unsigned char)(rng() & 0xFF);
        out[i] = char((unsigned char)cipher[i] ^ kb);
    }

    return out;
}
