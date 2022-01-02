#include "processor.h"
#include <chrono>
#include <thread>

using namespace std;
// Done: Return the aggregate CPU utilization
float Processor::Utilization() {
    vector<string> cpu;
    cpu = LinuxParser::CpuUtilization();
    assert(cpu.front() == "cpu");
    cpu.erase(cpu.begin());
    for(const string& word: cpu){
        cpu_times_old.push_back(stoull(word));
    }

    // sleep for delta calculation
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    cpu = LinuxParser::CpuUtilization();
    assert(cpu.front() == "cpu");
    cpu.erase(cpu.begin());
    for(const string& word: cpu){
        cpu_times_new.push_back(stoull(word));
    }

    //cpu_times: user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice

    // Old cpu time units

    //idle + iowait
    cpu_idle_old = cpu_times_old[LinuxParser::CPUStates::kIdle_]
            + cpu_times_old[LinuxParser::CPUStates::kIOwait_];
    // user + nice + system + irq + softirq + steal
    cpu_non_idle_old = cpu_times_old[LinuxParser::CPUStates::kUser_]
            + cpu_times_old[LinuxParser::CPUStates::kNice_]
            + cpu_times_old[LinuxParser::CPUStates::kSystem_]
            + cpu_times_old[LinuxParser::CPUStates::kIRQ_]
            + cpu_times_old[LinuxParser::CPUStates::kSoftIRQ_]
            + cpu_times_old[LinuxParser::CPUStates::kSteal_];
    cpu_total_old = cpu_idle_old + cpu_non_idle_old;

    //idle + iowait
    cpu_idle_new = cpu_times_new[LinuxParser::CPUStates::kIdle_]
                   + cpu_times_new[LinuxParser::CPUStates::kIOwait_];
    // user + nice + system + irq + softirq + steal
    cpu_non_idle_new = cpu_times_new[LinuxParser::CPUStates::kUser_]
                       + cpu_times_new[LinuxParser::CPUStates::kNice_]
                       + cpu_times_new[LinuxParser::CPUStates::kSystem_]
                       + cpu_times_new[LinuxParser::CPUStates::kIRQ_]
                       + cpu_times_new[LinuxParser::CPUStates::kSoftIRQ_]
                       + cpu_times_new[LinuxParser::CPUStates::kSteal_];
    cpu_total_new = cpu_idle_new + cpu_non_idle_new;

    return float((cpu_total_new-cpu_total_old) - (cpu_idle_new-cpu_idle_old))/float((cpu_total_new-cpu_total_old));
}