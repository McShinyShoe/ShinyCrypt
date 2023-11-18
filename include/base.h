#pragma once
#ifndef SHINY_BASE_LIB
#define SHINY_BASE_LIB 1.1

#include <cstddef>
#include <unordered_map>
#include <string>
#include <initializer_list>

namespace shiny {
    class Base {
    private:
        std::unordered_map<size_t, char> charMap;
        std::unordered_map<char, size_t> numMap;
        
    public:
        inline size_t radix() const { return charMap.size(); }
        size_t encode(const char& chr) const;
        size_t encode(std::string str) const;
        const char& find(const size_t& index) const;
        std::string decode(size_t num) const;
        std::string decodeN(size_t num, size_t N) const;

        Base() = delete;
        Base(const Base& other);
        Base(const char* chars, size_t radix);
        Base(const char* chars);
        Base(std::initializer_list<char> list);
    };
    extern const Base base2;
    extern const Base base8;
    extern const Base base10;
    extern const Base base16;
    extern const Base BASE16;
    extern const Base& binary;
    extern const Base& octal;
    extern const Base& decimal;
    extern const Base& hexadecimal;
    extern const Base& HEXADECIMAL;
}
#endif