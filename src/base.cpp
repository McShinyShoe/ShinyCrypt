#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <string>
#include <unordered_map>

#include "../include/base.h"

namespace shiny {
    size_t Base::encode(char chr) const {
        if (numMap.find(chr) == numMap.end()) return -1;
        return numMap.at(chr);
    }

    size_t Base::encode(std::string str) const {
        size_t multiplier = 1;
        size_t r = 0;
        size_t t;
        for (auto it = str.rbegin(); it != str.rend(); it++) {
            if ((t = encode(*it)) == -1) return -1;
            r += t * multiplier;
            multiplier *= radix();
        }
        return r;
    }

    const char &Base::find(size_t index) const {
        if (charMap.find(index) == charMap.end()) return EOF;
        return charMap.at(index);
    }

    std::string Base::decode(size_t num) const {
        if (num == 0) return std::string(1, charMap.at(0));
        std::string r;
        while (num) {
            r.push_back(charMap.at(num % radix()));
            num /= radix();
        }
        std::reverse(r.begin(), r.end());
        return r;
    }

    std::string Base::decodeN(size_t num, size_t N) const {
        std::string r;
        while (N--) {
            r.push_back(charMap.at(num % radix()));
            num /= radix();
        }
        std::reverse(r.begin(), r.end());
        return r;
    }

    Base::Base(const Base &other) {
        charMap = other.charMap;
        numMap = other.numMap;
    };

    Base::Base(const char *chars, size_t radix) {
        while (radix--) {
            charMap[radix] = chars[radix];
            numMap[chars[radix]] = radix;
        }
    };

    Base::Base(const char *chars) {
        size_t i = 0;
        while (chars[i]) {
            charMap[i] = chars[i];
            numMap[chars[i]] = i;
            i++;
        }
    };

    Base::Base(std::initializer_list<char> list) {
        size_t i = 0;
        for (const char &chr : list) {
            charMap[i] = chr;
            numMap[chr] = i;
            i++;
        }
    };

    const Base base2("01");
    const Base base8("01234567");
    const Base base10("0123456789");
    const Base base16("0123456789abcdef");
    const Base BASE16("0123456789ABCDEF");
    const Base &binary = base2;
    const Base &octal = base8;
    const Base &decimal = base10;
    const Base &hexadecimal = base16;
    const Base &HEXADECIMAL = BASE16;
}
