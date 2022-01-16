#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using namespace std;



// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
    filestream.close();
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
    string os, version, kernel;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
        stream.close();
    }
    return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
    vector<int> pids;
    DIR* directory = opendir(kProcDirectory.c_str());
    struct dirent* file;
    int (*predicate)(int) = std::isdigit;
    while ((file = readdir(directory)) != nullptr) {
        // Is this a directory?
        if (file->d_type == DT_DIR) {
          // Is every character of the name a digit?
          string filename(file->d_name);

          if (all_of(filename.begin(), filename.end(), predicate)) {
            int pid = stoi(filename);
            pids.push_back(pid);
          }
        }
    }
    closedir(directory);
    return pids;
}

// Done: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    string line, key, value;
    float mem_total=0.0, mem_free=0.0, cached_mem=0.0;
    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                if (key == "MemTotal") {mem_total = stof(value);}
                else if (key == "MemFree") {mem_free = stof(value);}
                else if (key == "Buffers" && key == "Cached"){cached_mem += stof(value);}
                else if (key == "Shmem"){cached_mem -= stof(value);}
                else if (key == "SReclaimable") {
                    cached_mem += stof(value);
                    filestream.close();
                    return (mem_total - mem_free - cached_mem) / mem_total;
                }
            }
        }
        filestream.close();
    }
    return 0.0;
}

// Done: Read and return the system uptime
long LinuxParser::UpTime() {
    string line, uptime;
    std::ifstream filestream(kProcDirectory + kUptimeFilename);
    if (filestream.is_open()) {
        filestream >> uptime;
        filestream.close();
        return stol(uptime);
    }
    return 0;
}

// Done: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
    string line, word;
    vector<string> cpu{};
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while (linestream >> word) {
                if (word == "cpu") {
                    cpu.push_back(word);
                    while (linestream >> word)
                        cpu.push_back(word);
                    filestream.close();
                    return cpu;
                }
            }
        }
        filestream.close();
    }
    return {};
}

// Done: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    string line, key, value;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "processes") {
                filestream.close();
                return stoi(value);
            }
        }
        filestream.close();
    }
    return 0;
}

// Done: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    string line, key, value;
    std::ifstream filestream(kProcDirectory + kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "procs_running") {
                filestream.close();
                return stoi(value);
            }
        }
    }
    filestream.close();
    return 0;
}

// Done: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
    string line;
    std::ifstream filestream(kProcDirectory + to_string(pid) +  kCmdlineFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        filestream.close();
        return line;
    }
    filestream.close();
    return {};
}

// Done: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
    string line, key, value;
    std::ifstream filestream(kProcDirectory + to_string(pid) +  kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "VmSize") {
                filestream.close();
                return to_string(int(stof(value)/1000));
            }
        }
    }
    filestream.close();
    return {};
}

// Done: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
    string line, key, value;
    std::ifstream filestream(kProcDirectory + to_string(pid) +  kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "Uid") {
                filestream.close();
                return value;
            }
        }
    }
    filestream.close();
    return {};
}

// Done: Read and return the user associated with a process
string LinuxParser::User(int pid) {
    string line, key, tmp, value, uid_ = Uid(pid);
    std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            linestream >> key >>tmp>> value;
            if (value == uid_) {
                filestream.close();
                return key;
            }
        }
    }
    filestream.close();
    return {};
}

// Done: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
    std::ifstream filestream(kProcDirectory + to_string(pid) +  kStatFilename);
    if (filestream.is_open()) {
        int counter = 1;
        string value;
        while(counter<=22){
            filestream >> value;
            counter++;
        }
        filestream.close();
        return LinuxParser::UpTime() - (stol(value)/ sysconf(_SC_CLK_TCK));
    }
    filestream.close();
    return 0;
}

float LinuxParser::CpuUtilization(int pid) {
    string word;
    float cpu_time{0};
    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
    int counter = 1;
    while (filestream.is_open()) {
        filestream >> word;
        if (counter == 14 || counter == 15 || counter == 16 || counter == 17){
            cpu_time += stof(word);
            if(counter==17)
                return cpu_time/float(sysconf(_SC_CLK_TCK));
        }
        counter++;
    }
    filestream.close();
    return cpu_time;
}