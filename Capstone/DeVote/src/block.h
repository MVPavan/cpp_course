//
// Created by pavanmv on 31/01/22.
//

#ifndef DEVOTE_BLOCK_H
#define DEVOTE_BLOCK_H

#include "imports.h"

//using namespace std;

class Block{
public:
    std::string prev_hash;
    Block(uint32_t b_idx, const std::string &b_data);
    std::string getHash();
    void mineBlock(uint32_t b_difficulty);


private:
    uint32_t b_Idx;
    int64_t b_Nounce;
    std::string b_Data;
    std::string b_Hash;
    time_t b_Time;

    static std::string difficulty_sub_str(uint32_t b_difficulty);

    std::string calculateHash() const;
};


#endif //DEVOTE_BLOCK_H
