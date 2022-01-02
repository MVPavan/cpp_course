#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <vector>
#include <string>

using ulli = unsigned long long int;
using vulli = std::vector<ulli>;

class Processor {
 public:
  float Utilization();  // Done: See src/processor.cpp
  // Done: Declare any necessary private members
 private:
    vulli cpu_times_old{},cpu_times_new{};
    static vulli loadCPUUtilization(std::vector<std::string>&);
    static float idleCPU(const vulli&);
    static float nonIdleCPU(const vulli&);
    static float deltaUtilization(const vulli&, const vulli&);
};

#endif