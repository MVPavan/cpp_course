#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include <vector>
#include <string>

using ulli = unsigned long long int;

class Processor {
 public:
  float Utilization();  // Done: See src/processor.cpp

  // Done: Declare any necessary private members
 private:
    // user, nice, system, idle, iowait, irq, softirq;
    std::vector<ulli> cpu_times_old{};
    std::vector<ulli> cpu_times_new{};
    ulli cpu_idle_old, cpu_non_idle_old, cpu_total_old, cpu_idle_new, cpu_non_idle_new, cpu_total_new;
};

#endif