#pragma once
#ifndef SHINY_BASE_LIB
#define SHINY_BASE_LIB 1.1

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace shiny {
    typedef std::pair<std::vector<uint64_t>, std::size_t> Encoded;
    class Base {
      private:
        std::unordered_map<uint64_t, char> charMap;
        std::unordered_map<char, uint64_t> numMap;

      public:
        inline uint64_t radix() const { return charMap.size(); }
        uint64_t encode(char chr) const;
        uint64_t encode(std::string str) const;
        Encoded encodeVec(std::string str) const;
        const char &find(uint64_t index) const;
        std::string decode(uint64_t num) const;
        std::string decodeVec(const Encoded &nums) const;
        std::string decodeN(uint64_t num, std::size_t N) const;

        Base() = delete;
        Base(const Base &other);
        Base(const char *chars, uint64_t radix);
        Base(const char *chars);
        Base(std::initializer_list<char> list);
    };
    extern const Base base2;
    extern const Base base8;
    extern const Base base10;
    extern const Base base16;
    extern const Base BASE16;
    extern const Base base32;
    extern const Base BASE32;
    extern const Base base64;
    extern const Base base64url;
    extern const Base ascii;
    extern const Base &binary;
    extern const Base &octal;
    extern const Base &decimal;
    extern const Base &hexadecimal;
    extern const Base &HEXADECIMAL;
}
#endif
