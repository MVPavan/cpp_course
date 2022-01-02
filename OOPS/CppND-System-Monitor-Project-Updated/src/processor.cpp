#include "processor.h"
#include <chrono>
#include <thread>

using namespace std;

vulli Processor::loadCPUUtilization(vector<string> & cpu) {
    vulli cpu_times{};
    assert(cpu.front() == "cpu");
    cpu.erase(cpu.begin());
    //cpu_times: user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice
    for(const string& word: cpu){
        cpu_times.push_back(stoull(word));
    }
    return cpu_times;
}

float Processor::idleCPU(const vulli& cpu_times){
    //idle + iowait
    return float(cpu_times[LinuxParser::CPUStates::kIdle_] + cpu_times[LinuxParser::CPUStates::kIOwait_]);
}

float Processor::nonIdleCPU(const vulli& cpu_times){
    // user + nice + system + irq + softirq + steal
    return float(cpu_times[LinuxParser::CPUStates::kUser_]
               + cpu_times[LinuxParser::CPUStates::kNice_]
               + cpu_times[LinuxParser::CPUStates::kSystem_]
               + cpu_times[LinuxParser::CPUStates::kIRQ_]
               + cpu_times[LinuxParser::CPUStates::kSoftIRQ_]
               + cpu_times[LinuxParser::CPUStates::kSteal_]
    );
}

float Processor::deltaUtilization(const vulli& cpu_old, const vulli& cpu_new){
    float idle_delta = idleCPU(cpu_new)- idleCPU(cpu_old);
    float total_delta = idleCPU(cpu_new) + nonIdleCPU(cpu_new) -idleCPU(cpu_old) - nonIdleCPU(cpu_old);
    return (total_delta-idle_delta)/total_delta;
}


// Done: Return the aggregate CPU utilization
float Processor::Utilization() {
    vector<string> cpu;
    cpu = LinuxParser::CpuUtilization();
    cpu_times_old = loadCPUUtilization(cpu);
    // sleep for delta calculation
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    cpu = LinuxParser::CpuUtilization();
    cpu_times_new = loadCPUUtilization(cpu);
    return deltaUtilization(cpu_times_old, cpu_times_new);
}