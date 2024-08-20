#pragma once
#ifndef SHINY_BASE_LIB
#define SHINY_BASE_LIB 1.1

#include <cstddef>
#include <initializer_list>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace shiny {
    typedef std::pair<std::vector<std::size_t>, std::size_t> Encoded;
    class Base {
      private:
        std::unordered_map<std::size_t, char> charMap;
        std::unordered_map<char, std::size_t> numMap;

      public:
        inline std::size_t radix() const { return charMap.size(); }
        std::size_t encode(char chr) const;
        std::size_t encode(std::string str) const;
        Encoded encodeVec(std::string str) const;
        const char &find(std::size_t index) const;
        std::string decode(std::size_t num) const;
        std::string decodeVec(Encoded nums) const;
        std::string decodeN(std::size_t num, std::size_t N) const;

        Base() = delete;
        Base(const Base &other);
        Base(const char *chars, std::size_t radix);
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
