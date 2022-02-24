//
// Created by pavanmv on 25/02/22.
//

#ifndef DEVOTE_MINER_H
#define DEVOTE_MINER_H

#include "imports.h"

class BlockMiner: public std::enable_shared_from_this<BlockMiner>{
public:
    explicit BlockMiner(BlockParams& b_params);
    BlockParams mineBlock(uint32_t b_difficulty);

protected:
    BlockParams b_params;

    std::mutex _mtx;
    std::condition_variable _cond_var;
    bool found_hash= false;


private:
    static std::string difficulty_sub_str(uint32_t b_difficulty);
    std::string calculateHash() const;

    void asyncMine(uint32_t b_difficulty, const std::string& sub_str);
};

bool check_async_threads(const std::vector<std::future<void>>& _futures);

#endif //DEVOTE_MINER_H
