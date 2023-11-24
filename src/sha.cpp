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
    void SHA1::init(std::string str) {
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
    void SHA1::compute() {
        for(size_t i = 0; i < blocks.size(); i++) {
            size_t j;
            for(j = 16; j < 80; j++)
                blocks[i][j] = ROTL(blocks[i][j - 3] ^ blocks[i][j - 8] ^ blocks[i][j - 14] ^ blocks[i][j - 16], 1);

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
    std::array<uint32_t, 5> SHA1::getDisgest() const {
        std::array<uint32_t, 5> r;
        for(int i = 0; i < 5; i++)
            r[i] = hashes[hashes.size() - 1][i];
        return r;
    }
    void SHA224::init(std::string str) {
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
    void SHA224::compute() {
        for(size_t i = 0; i < blocks.size(); i++) {
            size_t j;
            for(j = 16; j < 64; j++)
                blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

            for(j = 0; j < 8; j++)
                hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

            uint32_t temp1 = 0, temp2 = 0;
            for(j = 0; j < 64; j++) {
                temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                hashes[i][7] = hashes[i][6];
                hashes[i][6] = hashes[i][5];
                hashes[i][5] = hashes[i][4];
                hashes[i][4] = hashes[i][3] + temp1;
                hashes[i][3] = hashes[i][2];
                hashes[i][2] = hashes[i][1];
                hashes[i][1] = hashes[i][0];
                hashes[i][0] = temp1 + temp2;
            }
            for(j = 0; j < 8; j++)
                hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
        }
    }
    std::array<uint32_t, 7> SHA224::getDisgest() const {
        std::array<uint32_t, 7> r;
        for(int i = 0; i < 7; i++)
            r[i] = hashes[hashes.size() - 1][i];
        return r;
    }
    void SHA256::init(std::string str) {
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
    void SHA256::compute() {
        for(size_t i = 0; i < blocks.size(); i++) {
            size_t j;
            for(j = 16; j < 64; j++)
                blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

            for(j = 0; j < 8; j++)
                hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

            uint32_t temp1 = 0, temp2 = 0;
            for(j = 0; j < 64; j++) {
                temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                hashes[i][7] = hashes[i][6];
                hashes[i][6] = hashes[i][5];
                hashes[i][5] = hashes[i][4];
                hashes[i][4] = hashes[i][3] + temp1;
                hashes[i][3] = hashes[i][2];
                hashes[i][2] = hashes[i][1];
                hashes[i][1] = hashes[i][0];
                hashes[i][0] = temp1 + temp2;
            }
            for(j = 0; j < 8; j++)
                hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
        }
    }
    std::array<uint32_t, 8> SHA256::getDisgest() const {
        std::array<uint32_t, 8> r;
        for(int i = 0; i < 8; i++)
            r[i] = hashes[hashes.size() - 1][i];
        return r;
    }
    void SHA384::init(std::string str) {
        size_t strSize = str.size() * 8;
        const size_t totalSize = (strSize + 1 + 128);
        const size_t paddingSize = (1024 - (totalSize % 1024)) % 1024;
        const size_t blockSize = (totalSize + paddingSize) / 1024;

        blocks.resize(blockSize);
        hashes.resize(blockSize);

        int i;    
        for(i = 0; i < str.size(); i++)
            blocks[i / 128][(i % 128) / 8] |= ((uint64_t)str[i]) << (8 * (7 - (i % 8)));
        blocks[i / 128][(i % 128) / 8] |= ((uint64_t)(1 << 7)) << (8 * (7 - (i % 8)));

        //blocks[blockSize - 1][14];
        blocks[blockSize - 1][15] = strSize;
    };
    void SHA384::compute() {
        for(size_t i = 0; i < blocks.size(); i++) {
            size_t j;
            for(j = 16; j < 80; j++)
                blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

            for(j = 0; j < 8; j++)
                hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

            uint64_t temp1 = 0, temp2 = 0;
            for(j = 0; j < 80; j++) {
                temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                hashes[i][7] = hashes[i][6];
                hashes[i][6] = hashes[i][5];
                hashes[i][5] = hashes[i][4];
                hashes[i][4] = hashes[i][3] + temp1;
                hashes[i][3] = hashes[i][2];
                hashes[i][2] = hashes[i][1];
                hashes[i][1] = hashes[i][0];
                hashes[i][0] = temp1 + temp2;
            }
            for(j = 0; j < 8; j++)
                hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
        }
    }
    std::array<uint64_t, 6> SHA384::getDisgest() const {
        std::array<uint64_t, 6> r;
        for(int i = 0; i < 6; i++)
            r[i] = hashes[hashes.size() - 1][i];
        return r;
    }
    void SHA512::init(std::string str) {
        size_t strSize = str.size() * 8;
        const size_t totalSize = (strSize + 1 + 128);
        const size_t paddingSize = (1024 - (totalSize % 1024)) % 1024;
        const size_t blockSize = (totalSize + paddingSize) / 1024;

        blocks.resize(blockSize);
        hashes.resize(blockSize);

        int i;    
        for(i = 0; i < str.size(); i++)
            blocks[i / 128][(i % 128) / 8] |= ((uint64_t)str[i]) << (8 * (7 - (i % 8)));
        blocks[i / 128][(i % 128) / 8] |= ((uint64_t)(1 << 7)) << (8 * (7 - (i % 8)));

        //blocks[blockSize - 1][14];
        blocks[blockSize - 1][15] = strSize;
    };
    void SHA512::compute() {
        for(size_t i = 0; i < blocks.size(); i++) {
            size_t j;
            for(j = 16; j < 80; j++)
                blocks[i][j] = LOWERCASE_SIGMA1(blocks[i][j - 2]) + blocks[i][j - 7] + LOWERCASE_SIGMA0(blocks[i][j - 15]) + blocks[i][j - 16];

            for(j = 0; j < 8; j++)
                hashes[i][j] = i == 0 ? stateInitial[j] : hashes[i - 1][j];

            uint64_t temp1 = 0, temp2 = 0;
            for(j = 0; j < 80; j++) {
                temp1 = hashes[i][7] + SIGMA1(hashes[i][4]) + CHOICE(hashes[i][4], hashes[i][5], hashes[i][6]) + constant[j] + blocks[i][j];
                temp2 = SIGMA0(hashes[i][0]) + MAJOR(hashes[i][0], hashes[i][1], hashes[i][2]);
                hashes[i][7] = hashes[i][6];
                hashes[i][6] = hashes[i][5];
                hashes[i][5] = hashes[i][4];
                hashes[i][4] = hashes[i][3] + temp1;
                hashes[i][3] = hashes[i][2];
                hashes[i][2] = hashes[i][1];
                hashes[i][1] = hashes[i][0];
                hashes[i][0] = temp1 + temp2;
            }
            for(j = 0; j < 8; j++)
                hashes[i][j] += i == 0 ? stateInitial[j] : hashes[i - 1][j];
        }
    }
    std::array<uint64_t, 8> SHA512::getDisgest() const {
        std::array<uint64_t, 8> r;
        for(int i = 0; i < 8; i++)
            r[i] = hashes[hashes.size() - 1][i];
        return r;
    }
}