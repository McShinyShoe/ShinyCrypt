#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include "sha_functions.h"

namespace shiny {
    class SHA0 {
    public:
        static constexpr uint32_t stateInitial[5] = {
            0x67452301,
            0xefcdab89,
            0x98badcfe,
            0x10325476,
            0xc3d2e1f0
        };
        struct {
            inline uint32_t operator[](const size_t index) const {
                static constexpr uint32_t constant[4] = {
                        0x5a827999,
                        0x6ed9eba1,
                        0x8f1bbcdc,
                        0xca62c1d6
                };
                return constant[index / 20];
            }
        }
        static constexpr constant = {};
    
    public:
        template<typename T>
        inline T F(T x, T y, T z, size_t t) {
            switch (t / 20)
            {
            case 0:
                return CHOICE(x, y ,z);
            case 1:
                return PARITY(x, y, z);
            case 2:
                return MAJOR(x, y, z);
            case 3:
                return PARITY(x, y, z);
            default:
                return T();
            }
        };
    private:
        std::vector<std::array<uint32_t, 80>> blocks;
        std::vector<std::array<uint32_t, 5>> hashes;

    public:
        void init(std::string str);
        void compute();
        std::array<uint32_t, 5> getDisgest() const;
    };
}