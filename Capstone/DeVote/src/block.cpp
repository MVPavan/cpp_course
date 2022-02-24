//
// Created by pavanmv on 18/02/22.
//

#include "block.h"

Block::Block(uint32_t b_idx, const std::string &b_data){
    b_params.b_Idx = b_idx;
    b_params.b_Data = b_data;
    b_params.b_Nounce = -1;
    b_params.b_Time = time(nullptr);
}

std::string Block::getHash() const {
    return b_params.b_Hash;
}

void Block::updateBlock(BlockParams& _b_params) {
    b_params = _b_params;
}

void Block::mine(uint32_t b_difficulty){
    auto bm = std::make_shared<BlockMiner>(b_params);
    b_params = bm->mineBlock(b_difficulty);
}









