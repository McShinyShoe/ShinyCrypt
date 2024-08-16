#pragma once
#include <cstddef>

namespace shiny {
    template <typename T> inline T ROTL(T x, size_t n) {
        size_t w = sizeof(n) * 8;
        return (x << n) | (x >> (w - n));
    };
    template <typename T> inline T ROTR(T x, size_t n) {
        size_t w = sizeof(n) * 8;
        return (x >> n) | (x << (w - n));
    };
    template <typename T> inline T CHOICE(T x, T y, T z) { return (x & y) ^ (~x & z); };
    template <typename T> inline T PARITY(T x, T y, T z) { return x ^ y ^ z; };
    template <typename T> inline T MAJOR(T x, T y, T z) { return (x & y) ^ (x & z) ^ (y & z); };
}
