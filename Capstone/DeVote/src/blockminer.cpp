//
// Created by pavanmv on 25/02/22.
//

#include "blockminer.h"

BlockMiner::BlockMiner(BlockParams& _b_params): b_params(_b_params) {
    found_hash = false;
    sub_str = difficulty_sub_str(b_params.b_difficulty);
}

bool BlockMiner::hash_found_flag() const {
    return found_hash;
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

void BlockMiner::asyncMine() {
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
            (t_hash.substr(0,b_params.b_difficulty) != sub_str) || (!found_hash)
            );
    u_lock.lock();
    if(!found_hash){
        b_params.b_Hash = std::move(t_hash);
        found_hash = true;
    }
}

BlockParams BlockMiner::get_params() const {
    return b_params;
}




