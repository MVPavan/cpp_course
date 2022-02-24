//
// Created by pavanmv on 31/01/22.
//

#include "blockchain.h"

int main(){
    BlockChain bChain = BlockChain(5);

    std::cout << "Mining block 1..." << std::endl;
    bChain.addBlock(Block(1, "Block 1 Data"));

    std::cout << "Mining block 2..." << std::endl;
    bChain.addBlock(Block(2, "Block 2 Data"));

    std::cout << "Mining block 3..." << std::endl;
    bChain.addBlock(Block(3, "Block 3 Data"));

    return 0;
}