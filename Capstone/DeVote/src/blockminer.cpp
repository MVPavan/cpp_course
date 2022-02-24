//
// Created by pavanmv on 25/02/22.
//

#include "blockminer.h"

BlockMiner::BlockMiner(BlockParams& _b_params): b_params(_b_params) {
}

std::string BlockMiner::difficulty_sub_str(uint32_t b_difficulty){
    char str_check[b_difficulty+1];
    for (uint32_t i=0; i< b_difficulty; i++){
        str_check[i] = '0';
    }
    str_check[b_difficulty] = '\0';
    std::string sub_str(str_check);
    return sub_str;
}

inline std::string BlockMiner::calculateHash() const {
    std::stringstream ss;
    ss << b_params.b_Idx << b_params.b_Time << b_params.b_Data << b_params.b_Nounce << b_params.prev_hash;
    return sha256(ss.str());
}

void BlockMiner::asyncMine(uint32_t b_difficulty, const std::string& sub_str) {
    std::unique_lock<std::mutex> u_lock(_mtx);
    std::string t_hash;
    std::cout << "Thread ID" << std::this_thread::get_id();
    do{
        if(b_params.b_Nounce%100 < 12){
            std::cout << "Thread ID" << std::this_thread::get_id();
        }
        u_lock.lock();
        b_params.b_Nounce++;
        u_lock.unlock();
        t_hash = calculateHash();
    } while (
            (t_hash.substr(0,b_difficulty) != sub_str) || (!found_hash)
            );
    u_lock.lock();
    if(!found_hash){
        b_params.b_Hash = std::move(t_hash);
        found_hash = true;
    }
}

BlockParams BlockMiner::mineBlock(uint32_t b_difficulty) {
    std::string sub_str = difficulty_sub_str(b_difficulty);
    found_hash = false;
    std::cout << "Spawning threads..." << std::endl;
    auto shared_block = std::shared_ptr<BlockMiner>(shared_from_this());
    std::vector<std::future<void>> _futures;
//    asyncMine(b_difficulty, sub_str);
//    auto out = std::async(std::launch::deferred, &Block::asyncMine, this, b_difficulty, sub_str);
    for(size_t i=0; i<10 ; i++){
        _futures.emplace_back(std::async(std::launch::deferred, &BlockMiner::asyncMine, this, b_difficulty, sub_str));
    }

    for(auto &ftr: _futures) {
        while ([&ftr]() {
            auto status = ftr.wait_for(std::chrono::nanoseconds(100));
            return status != std::future_status::ready;
        }() || found_hash
                ){
        }
    }
//    while(!found_hash){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//    }
    if(!check_async_threads(_futures)){
        std::exit(-1);
    }
    return b_params;
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