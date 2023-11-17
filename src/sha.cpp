#include <cstdint>
#include <cstddef>
#include <vector>
#include <array>
#include <string>
#include "../include/sha.h"
#include "../include/sha_functions.h"

namespace shiny {
        void SHA0::init(std::string str) {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 64);
            const size_t paddingSize = (512 - (totalSize % 512)) % 512;
            const size_t blockSize = (totalSize + paddingSize) / 512;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 64][(i % 64) / 4] |= ((uint32_t)str[i]) << (8 * (3 - (i % 4)));
            blocks[i / 64][(i % 64) / 4] |= ((uint32_t)(1 << 7)) << (8 * (3 - (i % 4)));

            blocks[blockSize - 1][14] = strSize >> 32;
            blocks[blockSize - 1][15] = strSize;
        };
        void SHA0::compute() {
            for(size_t i = 0; i < blocks.size(); i++) {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = blocks[i][j - 3] ^ blocks[i][j - 8] ^ blocks[i][j - 14] ^ blocks[i][j - 16];

                for(j = 0; j < 5; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint32_t temp = 0;
                for(j = 0; j < 80; j++) {
                    temp = ROTL(hashes[i][0], 5) + F(hashes[i][1], hashes[i][2], hashes[i][3], j) + hashes[i][4] + constant[j] + blocks[i][j];
                    hashes[i][4] = hashes[i][3];
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = ROTL(hashes[i][1], 30);
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp;
                }
                for(j = 0; j < 5; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 5> SHA0::getDisgest() const {
            std::array<uint32_t, 5> r;
            for(int i = 0; i < 5; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
        void SHA1::init(std::string str)
        {
            size_t strSize = str.size() * 8;
            const size_t totalSize = (strSize + 1 + 64);
            const size_t paddingSize = (512 - (totalSize % 512)) % 512;
            const size_t blockSize = (totalSize + paddingSize) / 512;

            blocks.resize(blockSize);
            hashes.resize(blockSize);

            int i;    
            for(i = 0; i < str.size(); i++)
                blocks[i / 64][(i % 64) / 4] |= ((uint32_t)str[i]) << (8 * (3 - (i % 4)));
            blocks[i / 64][(i % 64) / 4] |= ((uint32_t)(1 << 7)) << (8 * (3 - (i % 4)));

            blocks[blockSize - 1][14] = strSize >> 32;
            blocks[blockSize - 1][15] = strSize;
        };
        void SHA1::compute()
        {
            for(size_t i = 0; i < blocks.size(); i++)
            {
                size_t j;
                for(j = 16; j < 80; j++)
                    blocks[i][j] = ROTL(blocks[i][j - 3] ^ blocks[i][j - 8] ^ blocks[i][j - 14] ^ blocks[i][j - 16], 1);

                for(j = 0; j < 5; j++)
                    hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

                uint32_t temp = 0;
                for(j = 0; j < 80; j++)
                {
                    temp = ROTL(hashes[i][0], 5) + F(hashes[i][1], hashes[i][2], hashes[i][3], j) + hashes[i][4] + constant[j] + blocks[i][j];
                    hashes[i][4] = hashes[i][3];
                    hashes[i][3] = hashes[i][2];
                    hashes[i][2] = ROTL(hashes[i][1], 30);
                    hashes[i][1] = hashes[i][0];
                    hashes[i][0] = temp;
                }
                for(j = 0; j < 5; j++)
                    hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
            }
        }
        std::array<uint32_t, 5> SHA1::getDisgest() const{
            std::array<uint32_t, 5> r;
            for(int i = 0; i < 5; i++)
                r[i] = hashes[hashes.size() - 1][i];
            return r;
        }
}