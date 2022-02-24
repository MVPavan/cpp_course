//
// Created by pavanmv on 18/02/22.
//

#include "block.h"

#include <utility>

Block::Block(uint32_t b_idx, const std::string &b_data){
    b_params.b_Idx = b_idx;
    b_params.b_Data = b_data;
    b_params.b_Nounce = -1;
    b_params.b_Time = time(nullptr);
    b_params.b_difficulty = 3;
}

std::string Block::getHash() const {
    return b_params.b_Hash;
}

void Block::updateBlock(BlockParams _b_params) {
    b_params = std::move(_b_params);
}

void Block::mineBlock(uint32_t b_difficulty){
    b_params.b_difficulty = b_difficulty;
    auto bm = std::make_shared<BlockMiner>(b_params);
    std::cout << "Spawning threads..." << std::endl;
    std::vector<std::future<void>> _futures;

    for(size_t i=0; i<10 ; i++){
        _futures.emplace_back(std::async(std::launch::async, &BlockMiner::asyncMine, bm));
    }

    for(auto &ftr: _futures) {
        while ([&ftr]() {
            auto status = ftr.wait_for(std::chrono::nanoseconds(100));
            return status != std::future_status::ready;
        }() || bm->hash_found_flag()
                ){
        }
    }
//    while(!found_hash){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//    }
    if(!check_async_threads(_futures)){
        std::exit(-1);
    }
    updateBlock(bm->get_params());
}

bool check_async_threads(const std::vector<std::future<void>>& _futures) {
    bool flag = true;
    std::for_each(_futures.begin(), _futures.end(), [flag](const std::future<void> &ftr)mutable
    {
        auto status = ftr.wait_for(std::chrono::nanoseconds(1));
        if(status != std::future_status::ready){
            std::cout << "Async not completed!!" <<std::endl;
            flag = false;
        }
    });
    return flag;
}







