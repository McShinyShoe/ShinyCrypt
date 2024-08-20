#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <string>
#include <unordered_map>

#include <cmath>
#include <iostream>

#include "../include/base.h"
#include "../include/bitmanip.h"

namespace shiny {
    std::size_t Base::encode(char chr) const {
        if (numMap.find(chr) == numMap.end()) return -1;
        return numMap.at(chr);
    }

    std::size_t Base::encode(std::string str) const {
        std::size_t multiplier = 1;
        std::size_t r = 0;
        std::size_t t;
        for (auto it = str.rbegin(); it != str.rend(); it++) {
            if ((t = encode(*it)) == -1) return -1;
            r += t * multiplier;
            multiplier *= radix();
        }
        return r;
    }

    Encoded Base::encodeVec(std::string str) const {
        const std::size_t bitCount = std::ceil(std::log2(radix()));
        const std::size_t substrLen = (sizeof(std::size_t) * 8) / bitCount;
        const std::size_t zeroPaddingCount = (sizeof(std::size_t) * 8) % bitCount;
        Encoded nums = {{}, str.size() * bitCount};
        Encoded temp = {{}, str.size() * bitCount};
        std::size_t min;

        for (std::size_t i = 0; i < str.size(); i += substrLen) {
            std::string substr = str.substr(i, substrLen);
            substr += std::string(substrLen - substr.size(), charMap.at(0));
            nums.first.push_back(encode(substr));
        };

        if (zeroPaddingCount != 0) {
            min = 0;
            for (std::size_t i = 0; i < nums.first.size(); i++) {
                if (i % 16 == 15) {
                    min++;
                    continue;
                }
                temp.first.push_back(0);
                temp.first.back() = 0;
                temp.first.back() |= nums.first.at(i) << (4 * (1 + ((i - min) % 15)));
                if (i + 1 != nums.first.size()) temp.first.back() |= nums.first.at(i + 1) >> ((sizeof(std::size_t) * 8) - (4 * (2 + ((i - min) % 15))));
            }
            return temp;
        }
        return nums;
    };

    const char &Base::find(uint64_t index) const {
        if (charMap.find(index) == charMap.end()) return EOF;
        return charMap.at(index);
    }

    std::string Base::decode(uint64_t num) const {
        if (num == 0) return std::string(1, charMap.at(0));
        std::string r;
        while (num) {
            r.push_back(charMap.at(num % radix()));
            num /= radix();
        }
        std::reverse(r.begin(), r.end());
        return r;
    }

    std::string Base::decodeVec(const Encoded &nums) const {
        std::string ret;
        const std::size_t bitCount = std::ceil(std::log2(radix()));
        const std::size_t substrLen = (sizeof(std::size_t) * 8) / bitCount;
        const std::size_t zeroPaddingCount = (sizeof(std::size_t) * 8) % bitCount;
        Encoded temp = {{}, nums.second};
        std::size_t bits = nums.second;

        if (zeroPaddingCount != 0) {
            for (std::size_t i = 0; i < nums.first.size(); i++) {
                if (i % (sizeof(std::size_t) * 8 / zeroPaddingCount - 1) == 0) { temp.first.push_back(nums.first.at(i) >> 4); }
                if (i % (sizeof(std::size_t) * 8 / zeroPaddingCount - 1) == (sizeof(std::size_t) * 8 / zeroPaddingCount - 2)) {
                    temp.first.push_back(nums.first.at(i) & BITMASK((sizeof(std::size_t) * 8) - zeroPaddingCount));
                    continue;
                };

                temp.first.push_back(0);
                temp.first.back() |= nums.first[i] << (sizeof(std::size_t) * 8 - zeroPaddingCount * (2 + (i % 15)));
                temp.first.back() |= nums.first[i + 1] >> (zeroPaddingCount * (2 + (i % 15)));
                temp.first.back() &= BITMASK((sizeof(std::size_t) * 8) - zeroPaddingCount);
            }
        }

        for (uint64_t num : (zeroPaddingCount ? temp.first : nums.first)) {
            if (bits / bitCount < substrLen) {
                ret += decodeN(num, substrLen).substr(0, bits / bitCount);
                break;
            }

            ret += decodeN(num, substrLen);
            bits -= substrLen * bitCount;
        };
        return ret;
    }

    std::string Base::decodeN(uint64_t num, std::size_t N) const {
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

    Base::Base(const char *chars, uint64_t radix) {
        while (radix--) {
            charMap[radix] = chars[radix];
            numMap[chars[radix]] = radix;
        }
    };

    Base::Base(const char *chars) {
        uint64_t i = 0;
        while (chars[i]) {
            charMap[i] = chars[i];
            numMap[chars[i]] = i;
            i++;
        }
    };

    Base::Base(std::initializer_list<char> list) {
        uint64_t i = 0;
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
    const Base base32("abcdefghijklmnopqrstuvwxyz234567");
    const Base BASE32("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567");
    const Base base64("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    const Base base64url("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_");
    const Base ascii({(char)0,   (char)1,   (char)2,   (char)3,   (char)4,   (char)5,   (char)6,   (char)7,   (char)8,   (char)9,   (char)10,  (char)11,  (char)12,
                      (char)13,  (char)14,  (char)15,  (char)16,  (char)17,  (char)18,  (char)19,  (char)20,  (char)21,  (char)22,  (char)23,  (char)24,  (char)25,
                      (char)26,  (char)27,  (char)28,  (char)29,  (char)30,  (char)31,  (char)32,  (char)33,  (char)34,  (char)35,  (char)36,  (char)37,  (char)38,
                      (char)39,  (char)40,  (char)41,  (char)42,  (char)43,  (char)44,  (char)45,  (char)46,  (char)47,  (char)48,  (char)49,  (char)50,  (char)51,
                      (char)52,  (char)53,  (char)54,  (char)55,  (char)56,  (char)57,  (char)58,  (char)59,  (char)60,  (char)61,  (char)62,  (char)63,  (char)(sizeof(std::size_t) * 8),
                      (char)65,  (char)66,  (char)67,  (char)68,  (char)69,  (char)70,  (char)71,  (char)72,  (char)73,  (char)74,  (char)75,  (char)76,  (char)77,
                      (char)78,  (char)79,  (char)80,  (char)81,  (char)82,  (char)83,  (char)84,  (char)85,  (char)86,  (char)87,  (char)88,  (char)89,  (char)90,
                      (char)91,  (char)92,  (char)93,  (char)94,  (char)95,  (char)96,  (char)97,  (char)98,  (char)99,  (char)100, (char)101, (char)102, (char)103,
                      (char)104, (char)105, (char)106, (char)107, (char)108, (char)109, (char)110, (char)111, (char)112, (char)113, (char)114, (char)115, (char)116,
                      (char)117, (char)118, (char)119, (char)120, (char)121, (char)122, (char)123, (char)124, (char)125, (char)126, (char)127, (char)128, (char)129,
                      (char)130, (char)131, (char)132, (char)133, (char)134, (char)135, (char)136, (char)137, (char)138, (char)139, (char)140, (char)141, (char)142,
                      (char)143, (char)144, (char)145, (char)146, (char)147, (char)148, (char)149, (char)150, (char)151, (char)152, (char)153, (char)154, (char)155,
                      (char)156, (char)157, (char)158, (char)159, (char)160, (char)161, (char)162, (char)163, (char)164, (char)165, (char)166, (char)167, (char)168,
                      (char)169, (char)170, (char)171, (char)172, (char)173, (char)174, (char)175, (char)176, (char)177, (char)178, (char)179, (char)180, (char)181,
                      (char)182, (char)183, (char)184, (char)185, (char)186, (char)187, (char)188, (char)189, (char)190, (char)191, (char)192, (char)193, (char)194,
                      (char)195, (char)196, (char)197, (char)198, (char)199, (char)200, (char)201, (char)202, (char)203, (char)204, (char)205, (char)206, (char)207,
                      (char)208, (char)209, (char)210, (char)211, (char)212, (char)213, (char)214, (char)215, (char)216, (char)217, (char)218, (char)219, (char)220,
                      (char)221, (char)222, (char)223, (char)224, (char)225, (char)226, (char)227, (char)228, (char)229, (char)230, (char)231, (char)232, (char)233,
                      (char)234, (char)235, (char)236, (char)237, (char)238, (char)239, (char)240, (char)241, (char)242, (char)243, (char)244, (char)245, (char)246,
                      (char)247, (char)248, (char)249, (char)250, (char)251, (char)252, (char)253, (char)254, (char)255});
    const Base &binary = base2;
    const Base &octal = base8;
    const Base &decimal = base10;
    const Base &hexadecimal = base16;
    const Base &HEXADECIMAL = BASE16;
}
