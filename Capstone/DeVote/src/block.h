//
// Created by pavanmv on 31/01/22.
//

#ifndef DEVOTE_BLOCK_H
#define DEVOTE_BLOCK_H

#include "imports.h"
#include "blockminer.h"
//using namespace std;


class Block{
public:
    std::string prev_hash;
    Block(uint32_t b_idx, const std::string &b_data);
    [[nodiscard]] std::string getHash() const;
    void mine(uint32_t b_difficulty);

private:
    struct BlockParams b_params;
    void updateBlock(BlockParams& b_params);

//    uint32_t b_Idx;
//    std::string b_Data;
//    std::string b_Hash;
//    int64_t b_Nounce;
//    time_t b_Time;
};

#endif //DEVOTE_BLOCK_H
