//
// Created by pavanmv on 18/02/22.
//

#ifndef DEVOTE_BLOCKCHAIN_H
#define DEVOTE_BLOCKCHAIN_H

#include "block.h"

class BlockChain{
public:
    BlockChain();
    void addBlock(Block b_new);

private:
    std::vector<Block> block_chain;
    uint32_t b_difficulty;
    Block getLastBlock() const;

};

#endif //DEVOTE_BLOCKCHAIN_H
