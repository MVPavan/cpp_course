//
// Created by pavanmv on 24/02/22.
//
#include "blockchain.h"

BlockChain::BlockChain(uint32_t chain_difficulty) : b_difficulty(chain_difficulty) {
    block_chain.emplace_back( std::move(Block(0, "Genesis Block")));

}

void BlockChain::addBlock(Block b_new) {
    b_new.prev_hash = getLastBlockHash();
    b_new.mine(b_difficulty);
    block_chain.emplace_back(std::move(b_new));
}
