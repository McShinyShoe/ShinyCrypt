#pragma once
#ifndef SHINY_BITMANIP_H
#define SHINY_BITMANIP_H

#include <cstddef>

namespace shiny {
    template <typename T> inline T ROTL(T x, std::size_t n) { return (x << n) | (x >> ((sizeof(n) * 8) - n)); };
    template <typename T> inline T ROTR(T x, std::size_t n) { return (x >> n) | (x << ((sizeof(n) * 8) - n)); };
    template <typename T> inline T CHOICE(T x, T y, T z) { return (x & y) ^ (~x & z); };
    template <typename T> inline T PARITY(T x, T y, T z) { return x ^ y ^ z; };
    template <typename T> inline T MAJOR(T x, T y, T z) { return (x & y) ^ (x & z) ^ (y & z); };
    template <typename T> inline T BITMASK(T n) { return ((((T(1) << (n - 1)) - 1) << 1) | 1); }
}

#endif