#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

// Done: Return this process's ID
int Process::Pid() const { return pid_; }

// Done: Return this process's CPU utilization
float Process::CpuUtilization() const {
    return LinuxParser::CpuUtilization(pid_)/float(LinuxParser::UpTime(pid_));
}

// Done: Return the command that generated this process
string Process::Command() const {
    string cmd = LinuxParser::Command(pid_);
    if(cmd.size() > 40){
        cmd  = cmd.substr(0, 40) + "...";
    }
    return cmd;
}

// Done: Return this process's memory utilization
string Process::Ram() const {
    return LinuxParser::Ram(pid_);
}
// Done: Return the user (name) that generated this process
string Process::User() const {
    return LinuxParser::User(pid_);
}
// Done: Return the age of this process (in seconds)
long int Process::UpTime() const {
    return LinuxParser::UpTime(pid_);
}
// Done: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return CpuUtilization() < a.CpuUtilization();
}