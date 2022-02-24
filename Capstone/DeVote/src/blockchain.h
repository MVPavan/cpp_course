//
// Created by pavanmv on 18/02/22.
//

#ifndef DEVOTE_BLOCKCHAIN_H
#define DEVOTE_BLOCKCHAIN_H

#include "block.h"

class BlockChain{
public:
    explicit BlockChain(uint32_t chain_difficulty=5);
    void addBlock(Block b_new);

private:
    std::vector<Block> block_chain;
    uint32_t b_difficulty;
    [[nodiscard]] std::string getLastBlockHash() const {
        return block_chain[-1].getHash();
    }

};

#endif //DEVOTE_BLOCKCHAIN_H
