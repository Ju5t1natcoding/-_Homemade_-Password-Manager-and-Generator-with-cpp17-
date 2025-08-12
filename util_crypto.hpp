#pragma once
#include <bits/stdc++.h>
using namespace std;

string to_hex(const string &data) {
    static const char *hex = "0123456789ABCDEF";
    string out;
    out.reserve(data.size()*2);
    for (unsigned char c : data) {
        out.push_back(hex[c >> 4]);
        out.push_back(hex[c & 0xF]);
    }
    return out;
}

string from_hex(const string &hexs) {
    string out;
    out.reserve(hexs.size()/2);
    auto val = [](char c)->int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return 0;
    };
    for (size_t i = 0; i+1 < hexs.size(); i += 2) {
        out.push_back(char((val(hexs[i]) << 4) | val(hexs[i+1])));
    }
    return out;
}

string now_timestamp() {
    using namespace std::chrono;
    auto t = system_clock::now();
    time_t tt = system_clock::to_time_t(t);
    tm *lt = localtime(&tt);
    ostringstream ss;
    ss << put_time(lt, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string gen_salt_bytes(size_t n = 8) {
    random_device rd;
    mt19937_64 g(rd());
    string s;
    s.resize(n);
    for (size_t i=0;i<n;i++) s[i] = char((g() >> (i%8)) & 0xFF);
    return s;
}
