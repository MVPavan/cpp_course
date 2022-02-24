//
// Created by pavanmv on 18/02/22.
//

#ifndef DEVOTE_IMPORTS_H
#define DEVOTE_IMPORTS_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <algorithm>

#include "sha256.h"

struct BlockParams{
    uint32_t b_Idx;
    std::string b_Data;
    std::string b_Hash;
    int64_t b_Nounce;
    time_t b_Time;
    std::string prev_hash;
};

#endif //DEVOTE_IMPORTS_H
