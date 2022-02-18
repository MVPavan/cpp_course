//
// Created by pavanmv on 18/02/22.
//

#include "block.h"
#include "blockchain.h"

Block::Block(uint32_t b_idx, const std::string &b_data): b_Idx(b_idx){
    b_Data = b_data;
    b_Nounce = -1;
    b_Time = time(nullptr);
}

std::string Block::getHash() {return b_Hash;}

std::string Block::difficulty_sub_str(uint32_t b_difficulty){
    char str_check[b_difficulty+1];
    for (uint32_t i=0; i< b_difficulty; i++){
        str_check[i] = '0';
    }
    str_check[b_difficulty] = '\0';
    std::string sub_str(str_check);
    return sub_str;
}

void Block::mineBlock(uint32_t b_difficulty) {
    std::string sub_str = difficulty_sub_str(b_difficulty);

}

inline std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << b_Idx << b_Time << b_Data << b_Nounce << prev_hash;

    return sha256(ss.str());
}