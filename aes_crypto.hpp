///De instalat Crypto++ pentru utilizare

#pragma once
#include "util_crypto.hpp"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
using namespace CryptoPP;

string aes_encrypt_with_password_hex(const string &plaintext, const string &password) {
    AutoSeededRandomPool prng;
    SecByteBlock salt(16); prng.GenerateBlock(salt, salt.size());
    SecByteBlock iv(AES::BLOCKSIZE); prng.GenerateBlock(iv, iv.size());
    SecByteBlock key(32);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    pbkdf.DeriveKey(key, key.size(), 0, (const byte*)password.data(), password.size(), salt, salt.size(), 20000, 0.0f);
    string cipher;
    CBC_Mode<AES>::Encryption enc;
    enc.SetKeyWithIV(key, key.size(), iv);
    StringSource ss(plaintext, true, new StreamTransformationFilter(enc, new StringSink(cipher), StreamTransformationFilter::PKCS_PADDING));
    string hex_salt, hex_iv, hex_cipher;
    StringSource(salt, salt.size(), true, new HexEncoder(new StringSink(hex_salt)));
    StringSource(iv, iv.size(), true, new HexEncoder(new StringSink(hex_iv)));
    StringSource(cipher, true, new HexEncoder(new StringSink(hex_cipher)));
    return hex_salt + ":" + hex_iv + ":" + hex_cipher;
}

string aes_decrypt_with_password_hex(const string &blob, const string &password) {
    auto p1 = blob.find(':');
    auto p2 = blob.find(':', p1 + 1);

    if (p1 == string::npos || p2 == string::npos) {
        return "";
    }

    string hex_salt = blob.substr(0, p1);
    string hex_iv   = blob.substr(p1 + 1, p2 - p1 - 1);
    string hex_cipher = blob.substr(p2 + 1);
    string salt, iv, cipher;
    StringSource(hex_salt, true, new HexDecoder(new StringSink(salt)));
    StringSource(hex_iv, true, new HexDecoder(new StringSink(iv)));
    StringSource(hex_cipher, true, new HexDecoder(new StringSink(cipher)));
    SecByteBlock key(32);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    pbkdf.DeriveKey(key, key.size(), 0, (const byte*)password.data(), password.size(), (const byte*)salt.data(), salt.size(), 20000, 0.0f);
    string recovered;

    try {
        CBC_Mode<AES>::Decryption dec;
        dec.SetKeyWithIV(key, key.size(), (const byte*)iv.data());
        StringSource ss(cipher, true, new StreamTransformationFilter(dec, new StringSink(recovered), StreamTransformationFilter::PKCS_PADDING));
    } catch(...) {
        return "";
    }

    return recovered;
}
