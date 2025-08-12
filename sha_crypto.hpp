#pragma once
#include "util_crypto.hpp"

using uint32 = unsigned int;
using uint64 = unsigned long long;
static const uint32 K_sha[64] = {
    0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u, 0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
    0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u, 0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
    0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu, 0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
    0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u, 0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
    0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u, 0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
    0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u, 0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
    0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u, 0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
    0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u, 0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u
};

uint32 rotr32(uint32 x, int n) {
    return (x >> n) | (x << (32 - n));
}

string sha256_hex(const string &msg) {
    vector<unsigned char> data(msg.begin(), msg.end());
    uint64 bitlen = uint64(data.size()) * 8;
    data.push_back(0x80);

    while ((data.size() % 64) != 56) {
        data.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        data.push_back((bitlen >> (i * 8)) & 0xFF);
    }

    uint32 h[8] = {
        0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au,
        0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u
    };

    for (size_t chunk=0; chunk < data.size(); chunk += 64) {
        uint32 w[64];
        for (int i = 0; i < 16; i++) {
            w[i] = (uint32(data[chunk + i * 4]) << 24) | (uint32(data[chunk + i * 4 + 1]) << 16) | (uint32(data[chunk + i * 4 + 2]) << 8) | (uint32(data[chunk + i * 4 + 3]));
        }

        for (int i = 16; i < 64; i++) {
            uint32 s0 = rotr32(w[i - 15], 7) ^ rotr32(w[i - 15], 18) ^ (w[i - 15] >> 3);
            uint32 s1 = rotr32(w[i - 2], 17) ^ rotr32(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32 a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], hh = h[7];
        for (int i = 0; i < 64; i++) {
            uint32 S1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
            uint32 ch = (e & f) ^ ((~e) & g);
            uint32 temp1 = hh + S1 + ch + K_sha[i] + w[i];
            uint32 S0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
            uint32 maj = (a & b) ^ (a & c) ^ (b & c);
            uint32 temp2 = S0 + maj;
            hh = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0]+=a;
        h[1]+=b;
        h[2]+=c;
        h[3]+=d;
        h[4]+=e;
        h[5]+=f;
        h[6]+=g;
        h[7]+=hh;
    }

    stringstream ss;
    ss << hex << setfill('0');

    for (int i = 0; i < 8; i++) {
        ss << setw(8) << h[i];
    }

    return ss.str();
}

string sha256_store_format(const string &plaintext) {
    string salt = gen_salt_bytes(8);
    string hexhash = sha256_hex(salt + plaintext);
    return to_hex(salt) + ":" + hexhash;
}
