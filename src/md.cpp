#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "../include/base.h"
#include "../include/md.h"

namespace shiny {
    void MD2::init(std::string str) {
        std::size_t padding = 16 - (str.size() % 16);
        str.append(std::string(padding, padding));

        message = std::vector<uint8_t>(str.begin(), str.end());
    };
    void MD2::compute() {
        std::array<uint8_t, 16> checksum({0});
        std::uint8_t L = 0;

        for (std::size_t i = 0; i < message.size() / 16; i++) {
            for (std::size_t j = 0; j < 16; j++) {
                uint8_t c = message[i * 16 + j];
                checksum[j] ^= sTable[c ^ L];
                L = checksum[j];
            }
        }

        message.insert(message.end(), checksum.begin(), checksum.end());
        disgest.fill(0);

        for (std::size_t i = 0; i < message.size() / 16; i++) {
            for (std::size_t j = 0; j < 16; j++) {
                disgest[16 + j] = message[i * 16 + j];
                disgest[32 + j] = (disgest[16 + j] ^ disgest[j]);
            }

            uint8_t t = 0;

            for (std::size_t j = 0; j < 18; j++) {
                for (std::size_t k = 0; k < 48; k++) { t = disgest[k] ^= sTable[t]; }
                t = (t + j) % 256;
            }
        }
    }
    std::array<uint8_t, 16> MD2::getDisgest() const {
        std::array<uint8_t, 16> ret;
        for (std::size_t i = 0; i < 16; i++) { ret[i] = disgest.at(i); }
        return ret;
    };
}
